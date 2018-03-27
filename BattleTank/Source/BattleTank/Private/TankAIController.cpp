// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"


void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();

	ATank* controlledTank = GetControlledTank();
	ATank* playerTank = GetPlayerTank();

	//auto owner = GetOwner();

	if (playerTank) // && owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("I have found player: %s"), *(playerTank->GetName()));
	}
	//else if (owner && !playerTank)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("%s has not found a Player tank"), *(owner->GetName()));
	//}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No playercontroller"));
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
