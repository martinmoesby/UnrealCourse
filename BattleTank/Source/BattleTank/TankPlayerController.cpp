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

	// Get worldLocation if linetrace throug crosshair
	// if it hists tha landscape
		// tell the controlled tank to ain at this point
}