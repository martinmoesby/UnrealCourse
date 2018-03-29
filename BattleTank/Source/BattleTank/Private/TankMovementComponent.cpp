// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntentMoveForward(float Throw)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s intends to move forward with %f"), *Name, Throw);
	if (!LeftTrack || !RightTrack) // Protect the pointers!!
	{ 
		UE_LOG(LogTemp, Error, TEXT("MovementComponent needs 2 track to move the tank."));
		return; 
	} 

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::Initialise(UTankTrack * LeftTrack, UTankTrack * RightTrack)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("Initilising tracks %s and %s "), *(LeftTrack->GetName()), *(RightTrack->GetName()));

	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}
