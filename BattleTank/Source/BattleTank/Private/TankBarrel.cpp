// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{
	// move the barrel in the right direction this frame
	// given a MAx Elevation sped and frame time
	UE_LOG(LogTemp, Warning, TEXT("Barrel elevate called as speed: %f"), DegreesPerSecond);
}