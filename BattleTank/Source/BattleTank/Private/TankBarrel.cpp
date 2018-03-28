// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// move the barrel in the right direction this frame
	// given a MAx Elevation sped and frame time
	// Clamp values to -1 and 1
	//if (RelativeSpeed > 1.0f) { RelativeSpeed = 1.f; }
	//if (RelativeSpeed < -1.0f) { RelativeSpeed = -1.f; }
	
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto ElevationChange = RelativeSpeed * BarrelElevationSpeed * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(Elevation, 0, 0));

	//auto TankName = GetOwner()->GetName();
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: %s reports : Aiming at speed: %f"), Time,*TankName, RelativeSpeed);

}