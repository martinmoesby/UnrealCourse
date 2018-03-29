//©2018 Martin Moesby 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntentMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntentTurnRight(float Throw);

	UFUNCTION(BLueprintCallable)
	void Initialise(UTankTrack* LeftTrack, UTankTrack* RightTrack);

private:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
