// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();

	//ATank* controlledTank = GetControlledTank();
	//ATank* playerTank = GetPlayerTank();

	//if (playerTank)
	//{
	//	controlledTank->AimAt(playerTank->GetActorLocation());
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("No playercontroller"));
	//}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );

	if (GetPlayerTank())
	{
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) // Protect your pointer !!!!!!!!!
	{
		return nullptr;
	}
	else
	{
		return Cast<ATank>(PlayerPawn);
	}
}
