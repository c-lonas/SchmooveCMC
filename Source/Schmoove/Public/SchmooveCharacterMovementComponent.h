#pragma once

#include "CoreMinimal.h"
#include "Schmoove.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SchmooveCharacterMovementComponent.generated.h"

UCLASS()

class SCHMOOVE_API USchmooveCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	class FSavedMove_Schmoove : public FSavedMove_Character
	{
		typedef FSavedMove_Character Super;

		uint8 Saved_bWantsToSprint:1;

		virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;
		virtual void Clear() override;
		virtual uint8 GetCompressedFlags() const override;
		virtual void SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
		virtual void PrepMoveFor(ACharacter* C) override;
	};

class FNetworkPredictionData_Client_Schmoove : public FNetworkPredictionData_Client_Character
{
public:
	FNetworkPredictionData_Client_Schmoove(const UCharacterMovementComponent& ClientMovement);

	typedef FNetworkPredictionData_Client_Character Super;

	virtual  FSavedMovePtr AllocateNewMove() override;
};
	

	bool Safe_bWantsToSprint;

public:
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
protected:
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;

public:
	USchmooveCharacterMovementComponent();
};