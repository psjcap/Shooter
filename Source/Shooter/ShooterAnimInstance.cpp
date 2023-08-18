// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UShooterAnimInstance::NativeInitializeAnimation()
{
	ShooterCharacter = Cast<AShooterCharacter>(this->TryGetPawnOwner());
}

void UShooterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if(ShooterCharacter != nullptr)
		ShooterCharacter = Cast<AShooterCharacter>(this->TryGetPawnOwner());

	if (ShooterCharacter != nullptr)
	{
		FVector Velocity = ShooterCharacter->GetVelocity();
		Speed = FMath::Sqrt(Velocity.X * Velocity.X + Velocity.Y * Velocity.Y);

		UCharacterMovementComponent* Movement = ShooterCharacter->GetCharacterMovement();
		bIsInAir = Movement->IsFalling();
		bIsAcceleration = Movement->GetCurrentAcceleration().Size() > 0.0f;

		FRotator AimRotator = ShooterCharacter->GetBaseAimRotation();
		FRotator MoveRotator = UKismetMathLibrary::MakeRotFromX(ShooterCharacter->GetVelocity());
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MoveRotator, AimRotator).Yaw;

		if (Speed > 0.0f)
			LastMovementOffsetYaw = MovementOffsetYaw;
	}
}