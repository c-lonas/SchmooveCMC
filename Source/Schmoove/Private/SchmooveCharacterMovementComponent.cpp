

#include "SchmooveCharacterMovementComponent.h"
#include "Schmoove.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"





bool USchmooveCharacterMovementComponent::FSavedMove_Schmoove::CanCombineWith(const FSavedMovePtr& NewMove,	ACharacter* InCharacter, float MaxDelta) const
{
	FSavedMove_Schmoove* NewSchmooveMove = static_cast<FSavedMove_Schmoove*>(NewMove.Get());

	if (Saved_bWantsToSprint != NewSchmooveMove->Saved_bWantsToSprint)
	{
		return false;
	}
	
	return FSavedMove_Character::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

void USchmooveCharacterMovementComponent::FSavedMove_Schmoove::Clear()
{
	FSavedMove_Character::Clear();

	Saved_bWantsToSprint = 0;
	
}

uint8 USchmooveCharacterMovementComponent::FSavedMove_Schmoove::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if (Saved_bWantsToSprint) Result |= FLAG_Custom_0;
	
	return Result;
}

void USchmooveCharacterMovementComponent::FSavedMove_Schmoove::SetMoveFor(ACharacter* C, float InDeltaTime,	FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	FSavedMove_Character::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);

	USchmooveCharacterMovementComponent* CharacterMovement = Cast<USchmooveCharacterMovementComponent>(C->GetCharacterMovement());

	Saved_bWantsToSprint = CharacterMovement->Safe_bWantsToSprint;
}

void USchmooveCharacterMovementComponent::FSavedMove_Schmoove::PrepMoveFor(ACharacter* C)
{
	Super::PrepMoveFor(C);

	USchmooveCharacterMovementComponent* CharacterMovement = Cast<USchmooveCharacterMovementComponent>(C->GetCharacterMovement());

	CharacterMovement->Safe_bWantsToSprint = Saved_bWantsToSprint;
}

USchmooveCharacterMovementComponent::FNetworkPredictionData_Client_Schmoove::FNetworkPredictionData_Client_Schmoove(const UCharacterMovementComponent& ClientMovement)
: Super(ClientMovement)
{
}

FSavedMovePtr USchmooveCharacterMovementComponent::FNetworkPredictionData_Client_Schmoove::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_Schmoove());
}

FNetworkPredictionData_Client* USchmooveCharacterMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != nullptr)

	if (ClientPredictionData == nullptr)
	{
		USchmooveCharacterMovementComponent* MutableThis = const_cast<USchmooveCharacterMovementComponent*>(this);

		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_Schmoove(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
	}
	return ClientPredictionData;
}

void USchmooveCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	Safe_bWantsToSprint = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
}

void USchmooveCharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation,	const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	if (MovementMode == MOVE_Walking)
	{
		if (Safe_bWantsToSprint)
		{
			MaxWalkSpeed = Sprint_MaxWalkSpeed;
		}
		else
		{
			MaxWalkSpeed = Walk_MaxWalkSpeed;
		}
	}
}




void USchmooveCharacterMovementComponent::SprintPressed()
{
	Safe_bWantsToSprint = true;
}

void USchmooveCharacterMovementComponent::SprintReleased()
{
	Safe_bWantsToSprint = false;
}

void USchmooveCharacterMovementComponent::CrouchPressed()
{
	bWantsToCrouch = !bWantsToCrouch;
}


USchmooveCharacterMovementComponent::USchmooveCharacterMovementComponent()
{
	NavAgentProps.bCanCrouch = true;
}