#include "Player/RACharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "InputCoreTypes.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"
#include "Player/RAPlayerController.h"
#include "RomaAeterna.h"
#include "UObject/ConstructorHelpers.h"

ARACharacter::ARACharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->JumpZVelocity = JumpVelocity;
	GetCharacterMovement()->AirControl = 0.35f;

	ThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonSpringArm"));
	ThirdPersonSpringArm->SetupAttachment(GetCapsuleComponent());
	ThirdPersonSpringArm->TargetArmLength = ThirdPersonCameraDistance;
	ThirdPersonSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
	ThirdPersonSpringArm->bUsePawnControlRotation = true;
	ThirdPersonSpringArm->bDoCollisionTest = true;
	ThirdPersonSpringArm->ProbeSize = 12.0f;
	ThirdPersonSpringArm->ProbeChannel = ECC_Camera;
	ThirdPersonSpringArm->bEnableCameraLag = true;
	ThirdPersonSpringArm->CameraLagSpeed = 14.0f;

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(ThirdPersonSpringArm, USpringArmComponent::SocketName);
	ThirdPersonCamera->bUsePawnControlRotation = false;
	ThirdPersonCamera->FieldOfView = ThirdPersonFieldOfView;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(8.0f, 0.0f, 68.0f));
	FirstPersonCamera->bUsePawnControlRotation = true;
	FirstPersonCamera->FieldOfView = FirstPersonFieldOfView;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	PlaceholderBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaceholderBody"));
	PlaceholderBody->SetupAttachment(GetCapsuleComponent());
	PlaceholderBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlaceholderBody->SetRelativeLocation(FVector(0.0f, 0.0f, -16.0f));
	PlaceholderBody->SetRelativeScale3D(FVector(0.55f, 0.55f, 1.25f));
	if (CylinderMesh.Succeeded())
	{
		PlaceholderBody->SetStaticMesh(CylinderMesh.Object);
	}

	PlaceholderHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaceholderHead"));
	PlaceholderHead->SetupAttachment(GetCapsuleComponent());
	PlaceholderHead->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlaceholderHead->SetRelativeLocation(FVector(0.0f, 0.0f, 66.0f));
	PlaceholderHead->SetRelativeScale3D(FVector(0.36f));
	if (SphereMesh.Succeeded())
	{
		PlaceholderHead->SetStaticMesh(SphereMesh.Object);
	}

	MoveAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_Move"));
	MoveAction->ValueType = EInputActionValueType::Axis2D;
	LookAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_Look"));
	LookAction->ValueType = EInputActionValueType::Axis2D;
	JumpAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_Jump"));
	SprintAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_Sprint"));
	ToggleViewAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_ToggleView"));
	PlayerMappingContext = CreateDefaultSubobject<UInputMappingContext>(TEXT("IMC_Player"));
	ConfigureInputMappings();

	ApplyViewMode(false);
}

void ARACharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentViewMode = InitialViewMode;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->JumpZVelocity = JumpVelocity;
	ThirdPersonSpringArm->TargetArmLength = ThirdPersonCameraDistance;
	FirstPersonCamera->FieldOfView = FirstPersonFieldOfView;
	ThirdPersonCamera->FieldOfView = ThirdPersonFieldOfView;
	ApplyViewMode(true);
}

void ARACharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	const APlayerController* PlayerController = Cast<APlayerController>(Controller);
	const ULocalPlayer* LocalPlayer = PlayerController ? PlayerController->GetLocalPlayer() : nullptr;
	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer ? LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>() : nullptr)
	{
		InputSubsystem->RemoveMappingContext(PlayerMappingContext);
		InputSubsystem->AddMappingContext(PlayerMappingContext, 0);
	}
}

void ARACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!ensureMsgf(EnhancedInput, TEXT("ARACharacter requires Enhanced Input as the default input component.")))
	{
		return;
	}

	EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARACharacter::HandleMove);
	EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARACharacter::HandleLook);
	EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInput->BindAction(SprintAction, ETriggerEvent::Started, this, &ARACharacter::HandleSprintStarted);
	EnhancedInput->BindAction(SprintAction, ETriggerEvent::Completed, this, &ARACharacter::HandleSprintCompleted);
	EnhancedInput->BindAction(ToggleViewAction, ETriggerEvent::Started, this, &ARACharacter::ToggleViewMode);
}

void ARACharacter::ConfigureInputMappings()
{
	FEnhancedActionKeyMapping& MoveRight = PlayerMappingContext->MapKey(MoveAction, EKeys::D);
	FEnhancedActionKeyMapping& MoveLeft = PlayerMappingContext->MapKey(MoveAction, EKeys::A);
	MoveLeft.Modifiers.Add(CreateDefaultSubobject<UInputModifierNegate>(TEXT("MoveLeftNegate")));

	FEnhancedActionKeyMapping& MoveForward = PlayerMappingContext->MapKey(MoveAction, EKeys::W);
	MoveForward.Modifiers.Add(CreateDefaultSubobject<UInputModifierSwizzleAxis>(TEXT("MoveForwardSwizzle")));
	FEnhancedActionKeyMapping& MoveBackward = PlayerMappingContext->MapKey(MoveAction, EKeys::S);
	MoveBackward.Modifiers.Add(CreateDefaultSubobject<UInputModifierSwizzleAxis>(TEXT("MoveBackwardSwizzle")));
	MoveBackward.Modifiers.Add(CreateDefaultSubobject<UInputModifierNegate>(TEXT("MoveBackwardNegate")));

	PlayerMappingContext->MapKey(LookAction, EKeys::Mouse2D);
	PlayerMappingContext->MapKey(JumpAction, EKeys::SpaceBar);
	PlayerMappingContext->MapKey(SprintAction, EKeys::LeftShift);
	PlayerMappingContext->MapKey(ToggleViewAction, EKeys::F9);
}

void ARACharacter::HandleMove(const FInputActionValue& Value)
{
	const FVector2D Movement = Value.Get<FVector2D>();
	if (!Controller)
	{
		return;
	}

	const FRotator ControlRotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);
	AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), Movement.Y);
	AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), Movement.X);
}

void ARACharacter::HandleLook(const FInputActionValue& Value)
{
	const FVector2D Look = Value.Get<FVector2D>() * LookSensitivity;
	AddControllerYawInput(Look.X);
	AddControllerPitchInput(Look.Y);
}

void ARACharacter::HandleSprintStarted()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ARACharacter::HandleSprintCompleted()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ARACharacter::ToggleViewMode()
{
	SetViewMode(CurrentViewMode == ERAViewMode::ThirdPerson ? ERAViewMode::FirstPerson : ERAViewMode::ThirdPerson);
}

void ARACharacter::SetViewMode(const ERAViewMode NewViewMode)
{
	if (CurrentViewMode == NewViewMode)
	{
		return;
	}

	CurrentViewMode = NewViewMode;
	ApplyViewMode(true);
}

void ARACharacter::ApplyViewMode(const bool bWriteLog)
{
	const bool bThirdPerson = CurrentViewMode == ERAViewMode::ThirdPerson;
	ThirdPersonCamera->SetActive(bThirdPerson);
	FirstPersonCamera->SetActive(!bThirdPerson);
	PlaceholderBody->SetVisibility(bThirdPerson, true);
	PlaceholderHead->SetVisibility(bThirdPerson, true);

#if !UE_BUILD_SHIPPING
	if (bWriteLog)
	{
		UE_LOG(LogRomaAeterna, Display, TEXT("Player camera mode: %s"), bThirdPerson ? TEXT("ThirdPerson") : TEXT("FirstPerson"));
	}
#endif
}

FText ARACharacter::GetViewModeDisplayName() const
{
	return CurrentViewMode == ERAViewMode::ThirdPerson
		? NSLOCTEXT("RomaAeterna", "ThirdPersonView", "Terza persona")
		: NSLOCTEXT("RomaAeterna", "FirstPersonView", "Prima persona");
}

bool ARACharacter::HasValidPlayableFoundation() const
{
	return ThirdPersonSpringArm && ThirdPersonCamera && FirstPersonCamera && PlaceholderBody && PlaceholderHead
		&& PlayerMappingContext && MoveAction && LookAction && JumpAction && SprintAction && ToggleViewAction
		&& WalkSpeed > 0.0f && SprintSpeed > WalkSpeed && JumpVelocity > 0.0f;
}
