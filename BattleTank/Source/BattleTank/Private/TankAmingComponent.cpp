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
	PrimaryComponentTick.bCanEverTick = true; // TODO Should this tick??
	UE_LOG(LogTemp, Warning, TEXT("%f: AimingComponent Construction"), FPlatformTime::Seconds());

	// ...
}

void UTankAmingComponent::BeginPlay() 
{
	LastFireTime = FPlatformTime::Seconds();
	FiringState = EFiringState::Ready;

	UE_LOG(LogTemp, Warning, TEXT("%f: AimingComponent BeginPlay"), FPlatformTime::Seconds());

}

void UTankAmingComponent::TickComponent(float DeltaTIme, ELevelTick TickType, FActorComponentTickFunction * TickFunction)
{
	UE_LOG(LogTemp, Warning, TEXT("%f: AimingComponent Ticking"), FPlatformTime::Seconds());

	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime)
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

void UTankAmingComponent::Initialise(UTankBarrel * Barrel, UTankTurrekt * Turret)
{
	this->Barrel = Barrel;
	this->Turret = Turret;
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

void UTankAmingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading) {

		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Muzzle")),
			Barrel->GetSocketRotation(FName("Muzzle"))
			);
		
		Projectile->LaunchProjectile(MuzzleVelocity);

		LastFireTime = FPlatformTime::Seconds();
	}
}

bool UTankAmingComponent::IsBarrelMoving()
{
	UE_LOG(LogTemp, Warning, TEXT("Barrel Vector: %s, AimDirection: %s"), *(Barrel->GetForwardVector().ToString()), *AimDirection.ToString());

	return !Barrel->GetForwardVector().Equals(AimDirection,0.1f);

}