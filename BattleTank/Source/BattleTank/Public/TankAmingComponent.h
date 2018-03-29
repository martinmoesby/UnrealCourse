//(c)2018 Martin Moesby
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAmingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Ready
};


// Forward declaration
class UTankBarrel; 
class UTankTurrekt;

/**
* Responsible for the aiming of the tank.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAmingComponent : public UActorComponent
{
	GENERATED_BODY()

	UTankAmingComponent();

public:	

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* Barrel, UTankTurrekt* Turret);

	void AimAt(FVector HitLocation);

protected:
	UPROPERTY(BlueprintReadonly, Category = "Status")
	EFiringState FiringState = EFiringState::Aiming;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurrekt* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float MuzzleVelocity = 4000.f;
	void MoveBarrelTowards(FVector AimDirection);
};
