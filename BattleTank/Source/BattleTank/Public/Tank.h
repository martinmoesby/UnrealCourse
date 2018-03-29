// (c)2018 Martin Moesby

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class UTankBarrel;
class UTankTurrekt;
class AProjectile;


/**
*
*/
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	//void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable)
	void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint; //Ensures only Components of Type AProjectile can be selected as Projectile in blueprint
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float MuzzleVelocity = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.f;

	UTankBarrel* Barrel = nullptr;
	double LastFireTime = 0;

};
