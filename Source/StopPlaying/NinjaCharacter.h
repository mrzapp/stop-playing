#pragma once

#include "GameFramework/Character.h"
#include "NinjaCharacter.generated.h"

/**
 * Pawns are the physical representations of players and creatures in a level.
 * Characters are Pawns that have a mesh, collision, and physics.
 */
UCLASS()
class STOPPLAYING_API ANinjaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANinjaCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	/** Allows a Pawn to set up custom input bindings. Called upon possession by a PlayerController, using the InputComponent created by CreatePlayerInputComponent(). */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:
	/** Apply momentum caused by damage. */
	virtual void ApplyDamageMomentum(float DamageTaken, const FDamageEvent& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser) override;

public:
	/** @return	Pawn's eye location */
	virtual FVector GetPawnViewLocation() const override;

public:
	/** Update location and rotation from ReplicatedMovement. Not called for simulated physics! */
	virtual void PostNetReceiveLocationAndRotation() override;

public:
	/**
	 * Set a pending launch velocity on the Character. This velocity will be processed on the next
	 * CharacterMovementComponent tick, and will set it to the "falling" state. Triggers the OnLaunched event.
	 * @note This version has a different behavior for the boolean parameters that take into account the Character's orientation.
	 * @param LaunchVelocity is the velocity to impart to the Character.
	 * @param bHorizontalOverride if true replace the horizontal part of the Character's velocity instead of adding to it.
	 * @param bVerticalOverride if true replace the vertical part of the Character's velocity instead of adding to it.
	 */
	UFUNCTION(Category = "Pawn|NinjaCharacter", BlueprintCallable)
	virtual void LaunchCharacterRotated(FVector LaunchVelocity, bool bHorizontalOverride, bool bVerticalOverride);

public:
	/** Returns NinjaCharacterMovement subobject **/
	FORCEINLINE class UNinjaCharacterMovementComponent* GetNinjaCharacterMovement() const;

public:
	/** Axis name for "move forward/back" control. This should match an Axis Binding in your input settings */
	UPROPERTY(Category = "Ninja Character", BlueprintReadOnly, EditDefaultsOnly)
	FString MoveForwardAxisName;

	/** Axis name for "move left/right" control. This should match an Axis Binding in your input settings */
	UPROPERTY(Category = "Ninja Character", BlueprintReadOnly, EditDefaultsOnly)
	FString MoveRightAxisName;

protected:
	/**
	 * Input handler for depth controls.
	 */
	virtual void MoveForward(float Value);

protected:
	/**
	 * Input handler for side controls.
	 */
	virtual void MoveRight(float Value);
};
