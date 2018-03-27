// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAmingComponent.h"

#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category=Setup)
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

protected:
	UTankAmingComponent* TankAimingComponent = nullptr;


private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, Category = Firing)
	float MuzzleVelocity = 100000.f; /// Starting point of 1000 m/sec.
};
