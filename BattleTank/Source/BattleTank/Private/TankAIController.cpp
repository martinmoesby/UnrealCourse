// (c)2018 Martin Moesby

#include "TankAIController.h"

#include "TankAmingComponent.h"

#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AI Controller Begin Play"));
	PrimaryActorTick.bCanEverTick = true;

}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UE_LOG(LogTemp, Warning, TEXT("AI Controller Tick"));

	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto controlledTank = GetPawn();

	if (!ensure(playerTank && controlledTank)) { return; }

	MoveToActor(playerTank, ProximityLimit);

	auto AimingComponent = controlledTank->FindComponentByClass<UTankAmingComponent>();
	AimingComponent->AimAt(playerTank->GetActorLocation());

	//controlledTank->Fire();
}
