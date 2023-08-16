// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystem.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = this->CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SocketOffset = FVector(0.0f, 50.0f, 50.0f);

	FollowCamera = this->CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	this->bUseControllerRotationPitch = false;
	this->bUseControllerRotationRoll = false;
	this->bUseControllerRotationYaw = true;

	UCharacterMovementComponent* Movement = this->GetCharacterMovement();
	Movement->bOrientRotationToMovement = false;
	Movement->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	Movement->JumpZVelocity = 600.0f;
	Movement->AirControl = 0.2f;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AShooterCharacter::MoveForward(float Value)
{
	if (Controller == nullptr)
		return;
	if (Value == 0.0f)
		return;

	FRotator ControllerRotation = this->GetControlRotation();
	FRotator YawRotation(0.0f, ControllerRotation.Yaw, 0.0f);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);	

	this->AddMovementInput(Direction, Value);
}

void AShooterCharacter::MoveRight(float Value)
{
	if (Controller == nullptr)
		return;
	if (Value == 0.0f)
		return;

	FRotator ControllerRotation = this->GetControlRotation();
	FRotator YawRotation(0.0f, ControllerRotation.Yaw, 0.0f);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	this->AddMovementInput(Direction, Value);
}

void AShooterCharacter::Turn(float Value)
{
	this->AddControllerYawInput(Value);
}

void AShooterCharacter::Lookup(float Value)
{
	this->AddControllerPitchInput(Value);
}

void AShooterCharacter::FireWeapon()
{
	if (FireSound != nullptr)
		UGameplayStatics::PlaySound2D(this, FireSound);

	const USkeletalMeshSocket* BarrelSocket = this->GetMesh()->GetSocketByName("BarrelSocket");
	if (BarrelSocket != nullptr)
	{
		FTransform SocketTransform = BarrelSocket->GetSocketTransform(this->GetMesh());
		if (MuzzleFlash != nullptr)
			UGameplayStatics::SpawnEmitterAtLocation(this->GetWorld(), MuzzleFlash, SocketTransform);

		if (GEngine != nullptr && GEngine->GameViewport != nullptr)
		{
			FVector2D ViewportSize;
			GEngine->GameViewport->GetViewportSize(ViewportSize);
			
			FVector2D ScreenPosition;
			ScreenPosition.X = ViewportSize.X / 2;
			ScreenPosition.Y = ViewportSize.Y / 2 - CameraBoom->SocketOffset.Y;

			FVector CrossHairWorldPosition;
			FVector CrossHairWorldDirection;
			bool bFindPosition = UGameplayStatics::DeprojectScreenToWorld(
				UGameplayStatics::GetPlayerController(this->GetWorld(), 0),
				ScreenPosition,
				CrossHairWorldPosition,
				CrossHairWorldDirection
			);

			if (bFindPosition)
			{
				FVector Start = CrossHairWorldPosition;
				FVector End = CrossHairWorldPosition + CrossHairWorldDirection * 50'000.0f;				
				FVector BeamEndPosition = End;

				FHitResult HitResult;
				this->GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility);
				if (HitResult.bBlockingHit)
				{
					UE_LOG(LogTemp, Warning, TEXT("bFindPosition"));

					if (ImpactParticle != nullptr)
						UGameplayStatics::SpawnEmitterAtLocation(this->GetWorld(), ImpactParticle, HitResult.Location);

					BeamEndPosition = HitResult.Location;
				}

				if (BeamParticle != nullptr)
				{
					UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(this->GetWorld(), BeamParticle, SocketTransform);
					if (Beam != nullptr)
						Beam->SetVectorParameter("Target", BeamEndPosition);
				}
			}
		}
	}

	if (HipFireMontage != nullptr)
	{
		UAnimInstance* AnimInstance = this->GetMesh()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(HipFireMontage);
			AnimInstance->Montage_JumpToSection("StartFire");
		}
	}
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ThisClass::Turn);
	PlayerInputComponent->BindAxis("Lookup", this, &ThisClass::Lookup);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ThisClass::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ThisClass::StopJumping);
	PlayerInputComponent->BindAction("FireButton", EInputEvent::IE_Pressed, this, &ThisClass::FireWeapon);
}

