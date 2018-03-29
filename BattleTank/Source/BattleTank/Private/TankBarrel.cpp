// (c)2018 Martin Moesby

#include "TankBarrel.h"

#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// move the barrel in the right direction this frame
	// given a MAx Elevation sped and frame time
	// Clamp values to -1 and 1
	
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto ElevationChange = RelativeSpeed * BarrelElevationSpeed * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(Elevation, 0, 0));

}