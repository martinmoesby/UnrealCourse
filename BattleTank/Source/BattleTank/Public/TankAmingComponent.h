// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAmingComponent.generated.h"

// Forward declaration
class UTankBarrel; 
class UTankTurrekt;

//Holds Barrels properties and Elevate Method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAmingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAmingComponent();
	void SetBarrelReference(UTankBarrel*);
	void SetTurretReference(UTankTurrekt*);

	void AimAt(FVector, float);

protected:

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurrekt* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
};
