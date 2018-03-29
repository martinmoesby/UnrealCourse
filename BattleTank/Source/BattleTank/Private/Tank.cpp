// (c)2018 Martin Moesby

#include "Tank.h"

#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAmingComponent.h"

#include "GameFramework/Pawn.h"
#include "Engine/StaticMeshSocket.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// No need to protect pointer as added at construction;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	TankAimingComponent = FindComponentByClass<UTankAmingComponent>();
	
}	



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("I'm here"));
		
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }

	TankAimingComponent->AimAt(HitLocation, MuzzleVelocity);


}

void ATank::Fire()
{

	if (!ensure(Barrel)) { return; }

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;

	if (isReloaded) {

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Muzzle")),
			Barrel->GetSocketRotation(FName("Muzzle"))
			);
		Projectile->LaunchProjectile(MuzzleVelocity);

		LastFireTime = FPlatformTime::Seconds();

	}

}