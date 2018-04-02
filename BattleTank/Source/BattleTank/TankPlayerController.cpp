// (c)2018 Martin Moesby

#include "TankPlayerController.h"

#include "Tank.h"
#include "TankAmingComponent.h"

#include "Engine/World.h"
#include "Public/CollisionQueryParams.h"



void ATankPlayerController::BeginPlay()
{

	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAmingComponent>();
	if (!ensure(AimingComponent)) {	return;	}

	FoundAimingComponent(AimingComponent);

}

void ATankPlayerController::SetPawn(APawn * InPawn)
{


	Super::SetPawn(InPawn);

	if (!InPawn) { return; }

	auto PossessedTank = Cast<ATank>(InPawn);

	//UE_LOG(LogTemp, Warning, TEXT("PossessedTank: %s"), *(PossessedTank->GetName()));

	// Subscribe our local method to the tank's death event
	PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);

}

void ATankPlayerController::OnPossessedTankDeath()
{
//	UE_LOG(LogTemp, Warning, TEXT("OK, my possessed tank is dead"));
//	GetPawn()->DetachFromControllerPendingDestroy();
	StartSpectatingOnly();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AimTowardsCrosshair();

}

void ATankPlayerController::AimTowardsCrosshair() 
{
	if (!GetPawn()) { return; } // e.g. Not possessing
	AimingComponent = GetPawn()->FindComponentByClass<UTankAmingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // Out parameter
	bool bHasGotFiringSolution = GetSightRayHitLocation(HitLocation);

	if (bHasGotFiringSolution)
	{
		AimingComponent->AimAt(HitLocation);
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
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Camera))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}