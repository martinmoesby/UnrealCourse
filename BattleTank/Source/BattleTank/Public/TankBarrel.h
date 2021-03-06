// (c)2018 Martin Moesby

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 moves down, +1 moves up, values clamped at -1 to 1
	void Elevate(float RelativeSpeed);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float BarrelElevationSpeed = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevation = 45.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevation = -1.5f;
};
