// (c)2018 Martin Moesby

#include "Tank.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// No need to protect pointer as added at construction;
}


void ATank::BeginPlay() 
{

	Super::BeginPlay();
	CurrentHealth = StartingHealth;

}

float ATank::GetHeatlhPercent() const
{
	return (float)CurrentHealth / (float) StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s has been damaged with %f point of damage by %s"), *GetName(), DamageAmount, *DamageCauser->GetName());
	auto DamageToApply = FMath::Clamp<int32>(FPlatformMath::RoundToInt(DamageAmount), 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0) {

		
		OnDeath.Broadcast();
	}	
	
	return DamageToApply;
}

