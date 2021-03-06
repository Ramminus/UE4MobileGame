// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Teamable.h"
#include "MobileGameCharacter.generated.h"

class UHealthModule;
class UEquipmentModule;
class USkeletalMeshComponent;
UCLASS(config=Game)
class AMobileGameCharacter : public ACharacter,  public ITeamable
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AMobileGameCharacter();

	void Tick(float DeltaTime);
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	bool InvertX;
	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	bool InvertY;
	//UPROPERTY()
	UHealthModule* HealthModule;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETeam Team;


protected:
	bool isTouching;
	float TouchX, TouchY;
	/** Weapon Skeletal mesh Component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		USkeletalMeshComponent* WeaponMeshComponent;
protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	UFUNCTION(BlueprintCallable, Category="Mesh")
	void SetWeaponMesh(USkeletalMesh* const WeaponMesh);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Team")
	ETeam GetTeam(); virtual ETeam GetTeam_Implementation() override;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attack")
		class UHealthModule* GetHealthModule(); virtual class UHealthModule* GetHealthModule_Implementation() override;

};

