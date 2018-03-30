// (c)2018 Martin Moesby

#include "TankTrack.h"

#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	ApplySidewaysForce();
	DriveTrack();
	CurrentThrottle = 0;
}

void UTankTrack::TickComponent(float DeltaTIme, ELevelTick TickType, FActorComponentTickFunction * TickFunction)
{
	Super::TickComponent(DeltaTIme, TickType, TickFunction);

}

void UTankTrack::ApplySidewaysForce()
{
	//Calculate the slippage speed
	auto slippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	// work out the required acceleration this fram to correct
	auto DeltaTIme = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -slippageSpeed / DeltaTIme * GetRightVector();
	// Calculate and apply sideways for (F = m*a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2; // There are two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::DriveTrack() {

	auto ForceApplied = GetForwardVector() * CurrentThrottle * MaxTrackDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(
		ForceApplied,
		ForceLocation
	);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -2, 2);
}

