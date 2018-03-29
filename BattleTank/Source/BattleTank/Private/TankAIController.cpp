// (c)2018 Martin Moesby

#include "TankAIController.h"

#include "Tank.h"

#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto controlledTank = Cast<ATank>(GetPawn());
	if (playerTank)
	{

		MoveToActor(playerTank, ProximityLimit);

		controlledTank->AimAt(playerTank->GetActorLocation());
		//controlledTank->Fire();
	}

}
