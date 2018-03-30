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
class AProjectile;

/**
* Responsible for the aiming of the tank.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAmingComponent : public UActorComponent
{
	GENERATED_BODY()


public:	

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* Barrel, UTankTurrekt* Turret);

	void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable)
	void Fire();

protected:
	UPROPERTY(BlueprintReadonly, Category = "Status")
	EFiringState FiringState = EFiringState::Aiming;

private:
	
	UTankAmingComponent();	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTIme, enum ELevelTick TickType, FActorComponentTickFunction* TickFunction) override;

	void MoveBarrelTowards(FVector AimDirection);

	bool IsBarrelMoving();	

	UTankBarrel* Barrel = nullptr;
	UTankTurrekt* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float MuzzleVelocity = 4000.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; //Ensures only Components of Type AProjectile can be selected as Projectile in blueprint

	double LastFireTime = 0;

	FVector AimDirection;
};
