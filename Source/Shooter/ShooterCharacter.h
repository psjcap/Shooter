// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void Lookup(float Value);
	void FireWeapon();
	void PressAimingButton();
	void ReleaseAimingButton();
	void WeaponFireButtonPressed();
	void WeaponFireButtonReleased();

	void UpdateFOV(float DeltaTime);
	void UpdateCrosshairSpreadMultiplier(float DeltaTime);

	UFUNCTION()
	void CrosshairWeaponFiredTimerEnd();
	UFUNCTION()
	void AutoWeaponFireTimerEnd();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	bool bWeaponFireButtonPressed;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class USoundCue* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* HipFireMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ImpactParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* BeamParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	bool bAiming;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float DefaultFOV;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float ZoomedFOV;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float ZoomedFOVInterpolateSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float CurrentFOV;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float AimRotateScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float NormalRotateScale;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float RotateScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Crosshair, meta = (AllowPrivateAccess = "true"))
	float CrosshairSpreadMultiplier;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Crosshair, meta = (AllowPrivateAccess = "true"))
	float CrosshairVelocityFactor;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Crosshair, meta = (AllowPrivateAccess = "true"))
	float CrosshairJumpFactor;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Crosshair, meta = (AllowPrivateAccess = "true"))
	float CrosshairAimFactor;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Crosshair, meta = (AllowPrivateAccess = "true"))
	bool bCrosshairWeaponFired;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Crosshair, meta = (AllowPrivateAccess = "true"))
	float CrosshairFireFactor;

public:
	FTimerHandle CrosshairWeaponFiredTimerHandle;
	FTimerHandle AutoWeaponFireTimerHandle;

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE bool GetAiming() const { return bAiming; }
	FORCEINLINE float GetCrosshairSpreadMultiplier() const { return CrosshairSpreadMultiplier; }
};
