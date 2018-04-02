// (c)2018 Martin Moesby

#include "TankAmingComponent.h"

#include "TankBarrel.h"
#include "TankTurrekt.h"
#include "Projectile.h"

#include "Kismet/GameplayStaticsTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UTankAmingComponent::UTankAmingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; 
	// ...
}

void UTankAmingComponent::BeginPlay() 
{
	LastFireTime = FPlatformTime::Seconds();
	FiringState = EFiringState::Reloading;

}

void UTankAmingComponent::TickComponent(float DeltaTIme, ELevelTick TickType, FActorComponentTickFunction * TickFunction)
{
	if (AmmoCount == 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else 	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Ready;
	}

}

void UTankAmingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurrekt * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAmingComponent::AimAt(FVector HitLocation)
{

	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }

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
		AimDirection = OutTossVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}

}

void UTankAmingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// get the difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAtRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAtRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch); 
	if (FMath::Abs(DeltaRotator.Yaw) <  180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else 
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	
}

void UTankAmingComponent::Fire()
{
	if (FiringState == EFiringState::Aiming || FiringState == EFiringState::Ready) 
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Muzzle")),
			Barrel->GetSocketRotation(FName("Muzzle"))
			);
		
		Projectile->LaunchProjectile(MuzzleVelocity);

		LastFireTime = FPlatformTime::Seconds();
		AmmoCount--;

	}
}

EFiringState UTankAmingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAmingComponent::GetAmmoCount() const
{
	return AmmoCount;
}

bool UTankAmingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	return !Barrel->GetForwardVector().Equals(AimDirection,0.1f);

}