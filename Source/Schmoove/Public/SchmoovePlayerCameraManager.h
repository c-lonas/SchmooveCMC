// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "SchmoovePlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class SCHMOOVE_API ASchmoovePlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly) float CrouchBlendDuration=.5f;
	float CrouchBlendTime;

public:
	ASchmoovePlayerCameraManager();

	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;
	
};
