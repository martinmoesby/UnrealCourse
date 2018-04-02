// (c)2018 Martin Moesby

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"






/**
*
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	FTankDelegate OnDeath;


protected:
	

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHeatlhPercent() const;

private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth = 100;

	//UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;
};
	
