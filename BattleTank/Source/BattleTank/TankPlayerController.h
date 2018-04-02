// (c)2018 Martin Moesby

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;
class UTankAmingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAmingComponent* AimComRef);

private:
	virtual void BeginPlay() override;
	virtual void Tick( float ) override;
	virtual void SetPawn(APawn * InPawn) override;

	UTankAmingComponent* AimingComponent = nullptr;


	// Starts to move the barrel towards the point where the crosshair hits the world
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation( FVector& ) const;
	bool GetLookDirection( FVector2D , FVector& ) const;
	bool GetLookVectorHitLocation( FVector& , FVector ) const;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditDefaultsOnly)
		float MaxRange = 1000000.0f;

	UFUNCTION()
	void OnPossessedTankDeath();
};
