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
#include "EngineUtils.h"
#include "Engine/TextRenderActor.h"
#include "Player/RAPlayerController.h"
#include "RomaAeterna.h"
#include "UObject/ConstructorHelpers.h"
#include "World/Modular/RARomanProceduralBuildingActor.h"
#include "World/Modular/RARomanVisualCatalog.h"

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
	PlaceholderBody->SetRelativeLocation(FVector(0.0f, 0.0f, 5.0f));
	PlaceholderBody->SetRelativeScale3D(FVector(0.42f, 0.30f, 0.72f));
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

	UStaticMesh* PlaceholderCylinderMesh = CylinderMesh.Object;
	auto ConfigureLimb = [this, PlaceholderCylinderMesh](UStaticMeshComponent* Limb, const FVector& Location, const FVector& Scale, const FRotator& Rotation)
	{
		Limb->SetupAttachment(GetCapsuleComponent());
		Limb->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Limb->SetRelativeLocation(Location);
		Limb->SetRelativeRotation(Rotation);
		Limb->SetRelativeScale3D(Scale);
		if (PlaceholderCylinderMesh) Limb->SetStaticMesh(PlaceholderCylinderMesh);
	};
	PlaceholderLeftArm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaceholderLeftArm"));
	ConfigureLimb(PlaceholderLeftArm, FVector(0, -35, 10), FVector(0.12f, 0.12f, 0.58f), FRotator(0, 0, -8));
	PlaceholderRightArm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaceholderRightArm"));
	ConfigureLimb(PlaceholderRightArm, FVector(0, 35, 10), FVector(0.12f, 0.12f, 0.58f), FRotator(0, 0, 8));
	PlaceholderLeftLeg = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaceholderLeftLeg"));
	ConfigureLimb(PlaceholderLeftLeg, FVector(0, -15, -58), FVector(0.15f, 0.15f, 0.70f), FRotator::ZeroRotator);
	PlaceholderRightLeg = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaceholderRightLeg"));
	ConfigureLimb(PlaceholderRightLeg, FVector(0, 15, -58), FVector(0.15f, 0.15f, 0.70f), FRotator::ZeroRotator);

	MoveAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_Move"));
	MoveAction->ValueType = EInputActionValueType::Axis2D;
	LookAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_Look"));
	LookAction->ValueType = EInputActionValueType::Axis2D;
	JumpAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_Jump"));
	SprintAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_Sprint"));
	ToggleViewAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_ToggleView"));
	ToggleHudAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_ToggleHud"));
	ToggleLabelsAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_ToggleLabels"));
	ToggleBoundsAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_ToggleBounds"));
	ToggleInteractionPointsAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_ToggleInteractionPoints"));
	RebuildBuildingsAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_RebuildBuildings"));
	ToggleUtilityNodesAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_ToggleUtilityNodes"));
	ToggleLocalAssetsAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_ToggleLocalAssets"));
	DecorationVariantAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_DecorationVariant"));
	ToggleRoofsAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_ToggleAccessibleRoofs"));
	ToggleDecorationFallbackAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_ToggleDecorationFallback"));
	ToggleRoomLabelsAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_ToggleRoomLabels"));
	InteractAction = CreateDefaultSubobject<UInputAction>(TEXT("IA_Interact"));
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
	EnhancedInput->BindAction(ToggleHudAction, ETriggerEvent::Started, this, &ARACharacter::ToggleTechnicalHud);
	EnhancedInput->BindAction(ToggleLabelsAction, ETriggerEvent::Started, this, &ARACharacter::ToggleBuildingLabels);
	EnhancedInput->BindAction(ToggleBoundsAction, ETriggerEvent::Started, this, &ARACharacter::ToggleCollisionBounds);
	EnhancedInput->BindAction(ToggleInteractionPointsAction, ETriggerEvent::Started, this, &ARACharacter::ToggleInteractionPoints);
	EnhancedInput->BindAction(RebuildBuildingsAction, ETriggerEvent::Started, this, &ARACharacter::RebuildRomanBuildings);
	EnhancedInput->BindAction(ToggleUtilityNodesAction, ETriggerEvent::Started, this, &ARACharacter::ToggleUtilityNodes);
	EnhancedInput->BindAction(ToggleLocalAssetsAction, ETriggerEvent::Started, this, &ARACharacter::ToggleLocalAssets);
	EnhancedInput->BindAction(DecorationVariantAction, ETriggerEvent::Started, this, &ARACharacter::CycleDecorationVariant);
	EnhancedInput->BindAction(ToggleRoofsAction, ETriggerEvent::Started, this, &ARACharacter::ToggleAccessibleRoofs);
	EnhancedInput->BindAction(ToggleDecorationFallbackAction, ETriggerEvent::Started, this, &ARACharacter::ToggleDecorationFallback);
	EnhancedInput->BindAction(ToggleRoomLabelsAction, ETriggerEvent::Started, this, &ARACharacter::ToggleRoomLabels);
	EnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, this, &ARACharacter::InteractWithNearestAccess);
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
	PlayerMappingContext->MapKey(ToggleHudAction, EKeys::F1);
	PlayerMappingContext->MapKey(ToggleLabelsAction, EKeys::F2);
	PlayerMappingContext->MapKey(ToggleBoundsAction, EKeys::F3);
	PlayerMappingContext->MapKey(ToggleInteractionPointsAction, EKeys::F4);
	PlayerMappingContext->MapKey(RebuildBuildingsAction, EKeys::F5);
	PlayerMappingContext->MapKey(ToggleUtilityNodesAction, EKeys::F6);
	PlayerMappingContext->MapKey(ToggleLocalAssetsAction, EKeys::F7);
	PlayerMappingContext->MapKey(DecorationVariantAction, EKeys::F8);
	PlayerMappingContext->MapKey(ToggleRoofsAction, EKeys::F10);
	PlayerMappingContext->MapKey(ToggleDecorationFallbackAction, EKeys::F11);
	PlayerMappingContext->MapKey(ToggleRoomLabelsAction, EKeys::F12);
	PlayerMappingContext->MapKey(InteractAction, EKeys::E);
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
	PlaceholderLeftArm->SetVisibility(bThirdPerson, true);
	PlaceholderRightArm->SetVisibility(bThirdPerson, true);
	PlaceholderLeftLeg->SetVisibility(bThirdPerson, true);
	PlaceholderRightLeg->SetVisibility(bThirdPerson, true);

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
		&& PlaceholderLeftArm && PlaceholderRightArm && PlaceholderLeftLeg && PlaceholderRightLeg
		&& PlayerMappingContext && MoveAction && LookAction && JumpAction && SprintAction && ToggleViewAction
		&& ToggleHudAction && ToggleLabelsAction && ToggleBoundsAction && ToggleInteractionPointsAction && RebuildBuildingsAction && ToggleUtilityNodesAction && ToggleLocalAssetsAction
		&& DecorationVariantAction && ToggleRoofsAction && ToggleDecorationFallbackAction && ToggleRoomLabelsAction && InteractAction
		&& WalkSpeed > 0.0f && SprintSpeed > WalkSpeed && JumpVelocity > 0.0f;
}

void ARACharacter::ToggleTechnicalHud() { bTechnicalHudVisible = !bTechnicalHudVisible; }

void ARACharacter::ToggleBuildingLabels()
{
	bBuildingLabelsVisible = !bBuildingLabelsVisible;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(GetWorld()); It; ++It) { It->bShowDebugLabels = bBuildingLabelsVisible; It->RebuildBuilding(); }
	for (TActorIterator<ATextRenderActor> It(GetWorld()); It; ++It) if (It->ActorHasTag(TEXT("RA_TECHNICAL_LABEL"))) It->SetActorHiddenInGame(!bBuildingLabelsVisible);
}

void ARACharacter::ToggleCollisionBounds()
{
	bCollisionBoundsVisible = !bCollisionBoundsVisible;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(GetWorld()); It; ++It) { It->bShowDebugBounds = bCollisionBoundsVisible; It->RebuildBuilding(); }
}

void ARACharacter::ToggleInteractionPoints()
{
	bInteractionPointsVisible = !bInteractionPointsVisible;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(GetWorld()); It; ++It) { It->bShowInteractionPoints = bInteractionPointsVisible; It->RebuildBuilding(); }
}

void ARACharacter::ToggleUtilityNodes()
{
	bUtilityNodesVisible = !bUtilityNodesVisible;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(GetWorld()); It; ++It) { It->bShowUtilityNodes = bUtilityNodesVisible; It->RebuildBuilding(); }
}

void ARACharacter::RebuildRomanBuildings()
{
	for (TActorIterator<ARARomanProceduralBuildingActor> It(GetWorld()); It; ++It) It->RebuildBuilding();
}

bool ARACharacter::AreLocalAssetsEnabled() const
{
	return URARomanVisualCatalog::AreLocalAssetsEnabled();
}

void ARACharacter::ToggleLocalAssets()
{
	const bool bEnable = !URARomanVisualCatalog::AreLocalAssetsEnabled();
	URARomanVisualCatalog::SetLocalAssetsEnabled(bEnable);
	for (TActorIterator<ARARomanProceduralBuildingActor> It(GetWorld()); It; ++It)
	{
		It->RefreshVisualCatalogFromLocalAssets();
		It->RebuildBuilding();
	}
	UE_LOG(LogRomaAeterna, Display, TEXT("%s"), bEnable && URARomanVisualCatalog::IsLocalCatalogAvailable()
		? TEXT("LOCAL_ASSETS_ACTIVE")
		: TEXT("PLACEHOLDER_FALLBACK_ACTIVE"));
}

void ARACharacter::CycleDecorationVariant()
{
	DecorationVariant = (DecorationVariant + 1) % 16;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(GetWorld()); It; ++It)
	{
		It->SetDecorationVariant(DecorationVariant);
	}
}

void ARACharacter::ToggleAccessibleRoofs()
{
	bAccessibleRoofsVisible = !bAccessibleRoofsVisible;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(GetWorld()); It; ++It)
	{
		It->SetRoofVisibility(bAccessibleRoofsVisible);
	}
}

void ARACharacter::ToggleDecorationFallback()
{
	bDecorationFallbacksForced = !bDecorationFallbacksForced;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(GetWorld()); It; ++It)
	{
		It->SetDecorationFallbackEnabled(bDecorationFallbacksForced);
	}
}

void ARACharacter::ToggleRoomLabels()
{
	bRoomLabelsVisible = !bRoomLabelsVisible;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(GetWorld()); It; ++It)
	{
		It->SetRoomLabelsVisible(bRoomLabelsVisible);
	}
}

void ARACharacter::InteractWithNearestAccess()
{
	ARARomanProceduralBuildingActor* Nearest = nullptr;
	double BestDistanceSquared = FMath::Square(450.0);
	for (TActorIterator<ARARomanProceduralBuildingActor> It(GetWorld()); It; ++It)
	{
		if (!It->IsAccessibleInteriorArchetype()) continue;
		const double DistanceSquared = FVector::DistSquared(GetActorLocation(), It->GetActorLocation());
		if (DistanceSquared < BestDistanceSquared)
		{
			BestDistanceSquared = DistanceSquared;
			Nearest = *It;
		}
	}
	if (Nearest)
	{
		Nearest->SetRoofVisibility(false);
		UE_LOG(LogRomaAeterna, Display, TEXT("Accesso tecnico aperto: %s"), *Nearest->GetName());
	}
}
