#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SYRIANVILLA_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	UOpenDoor();
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    void InitializeRotations();
    void CheckPressurePlatesExist();
    void SetActorThatOpensDoor();
    void CheckDoorStatus(float DeltaTime);
    void OpenADoor(float DeltaTime);
    void CloseADoor(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	    
private:
    FRotator DoorInitialRotation, DoorCurrentRotation, DoorTargetRotation;
    float DoorLastOpened = 0.f, DoorCloseDelay = 2.f;
    
    UPROPERTY(EditAnywhere)
    float DoorTargetYaw = 70.f;
    
    UPROPERTY(EditAnywhere);
    ATriggerVolume* PressurePlate;
    
    UPROPERTY(EditAnywhere);
    AActor* ActorThatOpensDoor;
};
