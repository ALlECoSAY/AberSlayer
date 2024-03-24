// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "Aberrable/Aberrable.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AberSlayerCharacter.generated.h"

class USplineComponent;
class UAberSlayerPlayerInventoryComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AAberSlayerCharacter : public ACharacter, public IAberrable
{
	GENERATED_BODY()


	
public:
	AAberSlayerCharacter();
	
	virtual void OnAberrate(bool bIsAberrated) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void ChangePointOfView();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay() override;

public:
	
#pragma region Getters/Setters
	/** Returns CameraBoom subobject **/
	FORCEINLINE TObjectPtr<USpringArmComponent> GetCameraBoom() const { return CameraBoom; }

	/** Returns ThirdPersonCamera subobject **/
	FORCEINLINE TObjectPtr<UCameraComponent> GetThirdPersonCamera() const { return ThirdPersonCamera; }

	FORCEINLINE TObjectPtr<UCameraComponent> GetFirstPersonCamera() const { return FirstPersonCamera; }
	FORCEINLINE TObjectPtr<UAberSlayerPlayerInventoryComponent> GetInventory() const { return Inventory; }

#pragma endregion Getters/Setters

protected:
	
#pragma region Components

	/** Camera boom positioning the camera behind the character */
	UPROPERTY
	(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** ThirdPerson camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> ThirdPersonCamera;

	/** FirstPerson camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAberSlayerPlayerInventoryComponent> Inventory;

#pragma endregion Components
#pragma region Input

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ChangePointOfViewAction;
#pragma endregion Input

	UPROPERTY()
	bool bIsFirstPersonView = false;
	
	UPROPERTY()
	TObjectPtr<AAberSlayerCharacter> TwinCharacter;
	
};

