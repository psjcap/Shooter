// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterHUD.h"
#include "Engine/Canvas.h"
#include "ShooterCharacter.h"

AShooterHUD::AShooterHUD(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer), 
	Size(64),
	SpreadSize(16)
{
}

void AShooterHUD::DrawHUD()
{
	AHUD::DrawHUD();

	const AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(this->GetOwningPawn());
	if (ShooterCharacter == nullptr)
		return;

	float SpreadMultiplier = ShooterCharacter->GetCrosshairSpreadMultiplier();

	float ScreenX = Canvas->SizeX * 0.5f - Size * 0.5f;
	float ScreenY = Canvas->SizeY * 0.5f - Size * 0.5f - 50.0f;

	if(CrossHairLeftTexture != nullptr)
		this->DrawTexture(CrossHairLeftTexture, ScreenX - SpreadSize * SpreadMultiplier, ScreenY, Size, Size, 0.0f, 0.0f, 1.0f, 1.0f);

	if (CrossHairTopTexture != nullptr)
		this->DrawTexture(CrossHairTopTexture, ScreenX, ScreenY - SpreadSize * SpreadMultiplier, Size, Size, 0.0f, 0.0f, 1.0f, 1.0f);

	if (CrossHairRightTexture != nullptr)
		this->DrawTexture(CrossHairRightTexture, ScreenX + SpreadSize * SpreadMultiplier, ScreenY, Size, Size, 0.0f, 0.0f, 1.0f, 1.0f);

	if (CrossHairBottomTexture != nullptr)
		this->DrawTexture(CrossHairBottomTexture, ScreenX, ScreenY + SpreadSize * SpreadMultiplier, Size, Size, 0.0f, 0.0f, 1.0f, 1.0f);
}