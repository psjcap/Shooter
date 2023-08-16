// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterHUD.h"
#include "Engine/Canvas.h"

AShooterHUD::AShooterHUD(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer), 
	Size(64)
{
}

void AShooterHUD::DrawHUD()
{
	AHUD::DrawHUD();

	if (CrossHairTexture != nullptr)
	{
		float ScreenX = Canvas->SizeX * 0.5f - Size * 0.5f;
		float ScreenY = Canvas->SizeY * 0.5f - Size * 0.5f - 50.0f;
		this->DrawTexture(CrossHairTexture, ScreenX, ScreenY, Size, Size, 0.0f, 0.0f, 1.0f, 1.0f);
	}
}