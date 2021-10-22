#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player's viewpoint
    FVector PlayerViewLocation;
    FRotator PlayerViewRotation;
    
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewLocation,
        OUT PlayerViewRotation);
    
    // Ray cast reach
    FVector LineTraceEndPoint = PlayerViewLocation + PlayerViewRotation.Vector() * Reach;
    DrawDebugLine(GetWorld(), PlayerViewLocation, LineTraceEndPoint, FColor(0,255,0), false, 0.f, 0, 5.f);
    
    // See what it hits
    FHitResult Hit;
    
    FCollisionQueryParams TraceParams(
        FName(TEXT("")),
        false,
        GetOwner()
    );
    
    GetWorld()->LineTraceSingleByObjectType(
        OUT Hit,
        PlayerViewLocation,
        LineTraceEndPoint,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParams
    );
    
    AActor* ActorHit = Hit.GetActor();
    
    if (ActorHit){
        UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *(ActorHit->GetName()));
    }
}

