// (c)2018 Martin Moesby

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UStaticMeshComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float Speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UProjectileMovementComponent * ProjectileMovement = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UParticleSystemComponent* LaunchBlast = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent *CollisionMesh = nullptr;
};
