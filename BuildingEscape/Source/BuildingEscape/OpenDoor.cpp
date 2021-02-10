// Copyright Cameron Davis 2021


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	StartingYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = StartingYaw;
	TargetYaw += StartingYaw;

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component, but no pressure plate has been assigned."), *GetOwner()->GetName());
	}
	
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor(DeltaTime);
	}
	else {
		CloseDoor(DeltaTime);
	}
}

// Open the door over a short period of time
void UOpenDoor::OpenDoor(float DeltaTime)
{
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2.0f);
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

// Close the door over a short period of time
void UOpenDoor::CloseDoor(float DeltaTime)
{
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	CurrentYaw = FMath::FInterpTo(CurrentYaw, StartingYaw, DeltaTime, 2.0f);
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

