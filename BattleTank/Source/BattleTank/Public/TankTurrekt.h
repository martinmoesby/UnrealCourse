// (c)2018 Martin Moesby

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurrekt.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurrekt : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Rotate(float ReletiveSpeed);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float RotationSpeed = 25.f;
	
	
};
