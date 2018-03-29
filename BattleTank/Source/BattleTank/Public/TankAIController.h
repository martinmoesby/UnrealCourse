// (c)2018 Martin Moesby

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"



class UTankAmingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

	virtual void Tick( float ) override;

	UTankAmingComponent* AimingComponent = nullptr;

	// How close will the AI tank com before stopping?
	float ProximityLimit = 3000.f; // Assumes this is in cm, thus 30 meters TODO Check unit of AcceptanceRadius property on MoveToActor
};
