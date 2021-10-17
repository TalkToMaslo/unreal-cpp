#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    
    InitializeRotations();
    CheckPressurePlatesExist();
    SetActorThatOpensDoor();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    CheckDoorStatus(DeltaTime);
}


void UOpenDoor::InitializeRotations()
{
    DoorInitialRotation = GetOwner()->GetActorRotation();
    DoorCurrentRotation = DoorInitialRotation;
    DoorTargetRotation = {DoorInitialRotation.Roll, DoorInitialRotation.Yaw + DoorTargetYaw, DoorInitialRotation.Pitch};
}


void UOpenDoor::CheckPressurePlatesExist() {
    if (!PressurePlate)
    
    {
            UE_LOG(LogTemp, Error, TEXT("%s has an OpenDoor component but does not have a pressure plate set"), *GetOwner()->GetName())
    }
}


void UOpenDoor::SetActorThatOpensDoor() {
    ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
}


void UOpenDoor::CheckDoorStatus(float DeltaTime)
{
    if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
    {
        OpenADoor(DeltaTime);
        DoorLastOpened = GetWorld()->GetTimeSeconds();
    }
    
    else if (PressurePlate && !PressurePlate->IsOverlappingActor(ActorThatOpensDoor) &&  GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
    {
        CloseADoor(DeltaTime);
    }
}

void UOpenDoor::OpenADoor(float DeltaTime)
{
    DoorCurrentRotation = FMath::RInterpConstantTo(DoorCurrentRotation, DoorTargetRotation, DeltaTime, 30);
    GetOwner()->SetActorRotation(DoorCurrentRotation);
}

void UOpenDoor::CloseADoor(float DeltaTime)
{
    DoorCurrentRotation = FMath::RInterpConstantTo(DoorCurrentRotation, DoorInitialRotation, DeltaTime, 45);
    GetOwner()->SetActorRotation(DoorCurrentRotation);
}


