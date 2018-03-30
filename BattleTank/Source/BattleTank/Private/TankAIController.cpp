// (c)2018 Martin Moesby

#include "TankAIController.h"

#include "TankAmingComponent.h"

#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto controlledTank = GetPawn();

	if (!ensure(playerTank && controlledTank)) { return; }

	MoveToActor(playerTank, ProximityLimit);

	auto AimingComponent = controlledTank->FindComponentByClass<UTankAmingComponent>();

	AimingComponent->AimAt(playerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Ready && DoFireAtPlayer)
	{
		AimingComponent->Fire();
	}
}
