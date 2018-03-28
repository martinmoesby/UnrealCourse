// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAmingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UTankAmingComponent::UTankAmingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAmingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

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
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveFiringSolution)
	{
		auto AimingAt = OutTossVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimingAt);

	}
}

void UTankAmingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// get the difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAtRotator = AimDirection.Rotation();
	auto DeltaRotator = BarrelRotator - AimAtRotator;
	Barrel->Elevate(5);
}