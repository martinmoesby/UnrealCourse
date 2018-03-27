// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Public/DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Public/CollisionQueryParams.h"


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
		GetControlledTank()->AimAt(HitLocation);
	}
}

/// Get worldLocation if linetrace throug crosshair, if it hists tha landscape return true
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const 
{
	// Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);

	// "De-Project" the screen position of the crosshair to  a world position
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along the look direction and see what we hit (up to a max-range)
		return GetLookVectorHitLocation(HitLocation, LookDirection);
	}
	
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
	);

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * MaxRange);

	//DrawDebugLine
	//(
	//	GetWorld(),
	//	StartLocation,
	//	EndLocation,
	//	FColor(255,0,0),
	//	false,
	//	0,
	//	0,
	//	3
	//);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}