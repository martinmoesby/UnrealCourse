//(c) 2018 Martin Moesby 

#include "TankMovementComponent.h"

#include "TankTrack.h"

void UTankMovementComponent::IntentMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; } // Protect the pointers!!
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntentTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; } // Protect the pointers!!
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// Get the direcetion the tank is heading
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	
	// Get the direction the tanks wants to move
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	// Calculate the Forward Throw that we vant the AI tank to move with...
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);

	// Calculate the Right Throw the we want the tank to turn with...
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	// Set the Tank Moving...
	IntentMoveForward(ForwardThrow);
	IntentTurnRight(RightThrow);

//	UE_LOG(LogTemp, Warning, TEXT("%s : Request Moving to : %s"),*TankName,*MoveVelocityNormal.ToString());

}

void UTankMovementComponent::Initialise(UTankTrack * LeftTrack, UTankTrack * RightTrack)
{
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}
