// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{

	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController NOT controlling a Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller controlling pawn: %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AimTowardsCrosshair();

	//UE_LOG(LogTemp, Warning, TEXT("Look, I'm ticking"));

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() 
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		// tell the controlled tank to aim at this point
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
	}
}

// Get worldLocation if linetrace throug crosshair, if it hists tha landscape return true
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const 
{
	// Calculate the location  from camera to crosshair
		// get the linetrace from camera to crosshair

	HitLocation = FVector(1.f);

	return false;
}