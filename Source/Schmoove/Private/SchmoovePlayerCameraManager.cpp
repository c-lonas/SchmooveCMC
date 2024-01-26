// Fill out your copyright notice in the Description page of Project Settings.

#include "SchmooveCharacterMovementComponent.h"
#include "SchmoovePlayerCameraManager.h"
#include "SchmooveCharacter.h"
#include "Components/CapsuleComponent.h"

ASchmoovePlayerCameraManager::ASchmoovePlayerCameraManager()
{
}

void ASchmoovePlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	Super::UpdateViewTarget(OutVT, DeltaTime);

	if (ASchmooveCharacter* SchmooveCharacter = Cast<ASchmooveCharacter>(GetOwningPlayerController()->GetPawn()))
	{
		USchmooveCharacterMovementComponent* ZMC = SchmooveCharacter->GetSchmooveCharacterMovement();
		FVector TargetCrouchOffset = FVector(
			0,
			0,
			ZMC->GetCrouchedHalfHeight() - SchmooveCharacter->GetClass()->GetDefaultObject<ACharacter>()->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()
		);
		FVector Offset = FMath::Lerp(FVector::ZeroVector, TargetCrouchOffset, FMath::Clamp(CrouchBlendTime / CrouchBlendDuration, 0.f, 1.f));

		if (ZMC->IsCrouching())
		{
			CrouchBlendTime = FMath::Clamp(CrouchBlendTime + DeltaTime, 0.f, CrouchBlendDuration);
			Offset -= TargetCrouchOffset;
		}
		else
		{
			CrouchBlendTime = FMath::Clamp(CrouchBlendTime - DeltaTime, 0.f, CrouchBlendDuration);
		}

		OutVT.POV.Location += Offset;
	}
	
}

