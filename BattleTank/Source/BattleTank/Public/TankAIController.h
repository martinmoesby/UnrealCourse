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
protected:
	// How close will the AI tank com before stopping?
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ProximityLimit = 8000.f; // Assumes this is in cm, thus 80 meters

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		bool DoFireAtPlayer = false;

private:
	virtual void BeginPlay() override;

	virtual void Tick( float ) override;

	UTankAmingComponent* AimingComponent = nullptr;

};
