// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShooterHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AShooterHUD : public AHUD
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CrossHair, meta = (AllowPrivateAccess = "true"))
	int32 Size;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CrossHair, meta = (AllowPrivateAccess = "true"))
	class UTexture* CrossHairTexture;

public:
	AShooterHUD(const FObjectInitializer& ObjectInitializer);
	virtual void DrawHUD() override;
};
