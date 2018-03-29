// Fill out your copyright notice in the Description page of Project Settings.

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

//Holds Barrels properties and Elevate Method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAmingComponent : public UActorComponent
{
	GENERATED_BODY()

	UTankAmingComponent();

public:	

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* Barrel, UTankTurrekt* Turret);

	// Sets default values for this component's properties
	//void SetBarrelReference(UTankBarrel*);
	//void SetTurretReference(UTankTurrekt*);

	void AimAt(FVector, float);

protected:
	UPROPERTY(BlueprintReadonly, Category = "Status")
	EFiringState FiringState = EFiringState::Aiming;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurrekt* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
};
