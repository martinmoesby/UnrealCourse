// (c)2018 Martin Moesby

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float MaxTrackDrivingForce = 30000.f; // Assume 40 ton tank and 1g acceleration 

private:

	UTankTrack();

	virtual void BeginPlay() override;	
	virtual void TickComponent(float DeltaTIme, ELevelTick TickType, FActorComponentTickFunction * TickFunction) override;
	
	void ApplySidewaysForce();
	void DriveTrack();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
 
	float CurrentThrottle = 0;

};
