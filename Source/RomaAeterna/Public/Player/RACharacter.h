#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RACharacter.generated.h"

class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UStaticMeshComponent;
struct FInputActionValue;

UENUM(BlueprintType)
enum class ERAViewMode : uint8
{
	FirstPerson UMETA(DisplayName = "First Person"),
	ThirdPerson UMETA(DisplayName = "Third Person")
};

UCLASS()
class ROMAAETERNA_API ARACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARACharacter();

	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Roma Aeterna|Camera")
	void ToggleViewMode();

	UFUNCTION(BlueprintCallable, Category = "Roma Aeterna|Camera")
	void SetViewMode(ERAViewMode NewViewMode);

	UFUNCTION(BlueprintPure, Category = "Roma Aeterna|Camera")
	ERAViewMode GetViewMode() const { return CurrentViewMode; }

	UFUNCTION(BlueprintPure, Category = "Roma Aeterna|Camera")
	FText GetViewModeDisplayName() const;

	bool HasValidPlayableFoundation() const;
	float GetConfiguredWalkSpeed() const { return WalkSpeed; }
	float GetConfiguredSprintSpeed() const { return SprintSpeed; }
	const UInputMappingContext* GetPlayerMappingContext() const { return PlayerMappingContext; }
	const USpringArmComponent* GetThirdPersonSpringArm() const { return ThirdPersonSpringArm; }
	const UCameraComponent* GetFirstPersonCamera() const { return FirstPersonCamera; }
	const UCameraComponent* GetThirdPersonCamera() const { return ThirdPersonCamera; }

protected:
	virtual void BeginPlay() override;

private:
	void ConfigureInputMappings();
	void ApplyViewMode(bool bWriteLog);
	void HandleMove(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);
	void HandleSprintStarted();
	void HandleSprintCompleted();

	UPROPERTY(VisibleAnywhere, Category = "Roma Aeterna|Camera")
	TObjectPtr<USpringArmComponent> ThirdPersonSpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Roma Aeterna|Camera")
	TObjectPtr<UCameraComponent> ThirdPersonCamera;

	UPROPERTY(VisibleAnywhere, Category = "Roma Aeterna|Camera")
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, Category = "Roma Aeterna|Prototype")
	TObjectPtr<UStaticMeshComponent> PlaceholderBody;

	UPROPERTY(VisibleAnywhere, Category = "Roma Aeterna|Prototype")
	TObjectPtr<UStaticMeshComponent> PlaceholderHead;

	UPROPERTY(VisibleAnywhere, Transient, Category = "Roma Aeterna|Input")
	TObjectPtr<UInputMappingContext> PlayerMappingContext;

	UPROPERTY(VisibleAnywhere, Transient, Category = "Roma Aeterna|Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(VisibleAnywhere, Transient, Category = "Roma Aeterna|Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(VisibleAnywhere, Transient, Category = "Roma Aeterna|Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(VisibleAnywhere, Transient, Category = "Roma Aeterna|Input")
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(VisibleAnywhere, Transient, Category = "Roma Aeterna|Input")
	TObjectPtr<UInputAction> ToggleViewAction;

	UPROPERTY(EditDefaultsOnly, Category = "Roma Aeterna|Movement", meta = (ClampMin = "1.0"))
	float WalkSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Roma Aeterna|Movement", meta = (ClampMin = "1.0"))
	float SprintSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Roma Aeterna|Movement", meta = (ClampMin = "1.0"))
	float JumpVelocity = 420.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Roma Aeterna|Input", meta = (ClampMin = "0.01"))
	float LookSensitivity = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Roma Aeterna|Camera", meta = (ClampMin = "100.0"))
	float ThirdPersonCameraDistance = 350.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Roma Aeterna|Camera", meta = (ClampMin = "60.0", ClampMax = "120.0"))
	float FirstPersonFieldOfView = 90.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Roma Aeterna|Camera", meta = (ClampMin = "60.0", ClampMax = "120.0"))
	float ThirdPersonFieldOfView = 85.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Roma Aeterna|Camera")
	ERAViewMode InitialViewMode = ERAViewMode::ThirdPerson;

	UPROPERTY(VisibleInstanceOnly, Category = "Roma Aeterna|Camera")
	ERAViewMode CurrentViewMode = ERAViewMode::ThirdPerson;
};
