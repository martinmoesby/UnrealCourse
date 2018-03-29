// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAmingComponent.h"
#include "TankBarrel.h"
#include "TankTurrekt.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UTankAmingComponent::UTankAmingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; // TODO Should this tick??

	// ...
}

void UTankAmingComponent::Initialise(UTankBarrel * Barrel, UTankTurrekt * Turret)
{
	this->Barrel = Barrel;
	this->Turret = Turret;
}

//void UTankAmingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
//{
//	Barrel = BarrelToSet;
//}
//
//void UTankAmingComponent::SetTurretReference(UTankTurrekt * TurretToSet)
//{
//	Turret = TurretToSet;
//}

void UTankAmingComponent::AimAt(FVector HitLocation, float MuzzleVelocity)
{

	if (!Barrel) { return; }

	auto WorldContextObject = this;
	FVector OutTossVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Muzzle"));
	bool bHaveFiringSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutTossVelocity,
		StartLocation,
		HitLocation,
		MuzzleVelocity,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveFiringSolution)
	{
		auto AimingAt = OutTossVelocity.GetSafeNormal();
		MoveBarrelTowards(AimingAt);
	}
	else
	{
		MoveBarrelTowards(FVector(0));
	}
}

void UTankAmingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// get the difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAtRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAtRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch); // TODO eliminate magic number
	Turret->Rotate(DeltaRotator.Yaw);

}