// Copyright Cameron Davis 2021


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

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

	FString LeftDoor = ("SM_DoorWay_Large_Door_Left_6");
	FString RightDoor = ("SM_DoorWay_Large_Door_Right_8");
	FString Door = GetOwner()->GetName();

	float OpenAngle = 0.f;

	if (Door == LeftDoor) {
		OpenAngle = 90.f;
	}
	else if (Door == RightDoor) {
		OpenAngle = -90.f;
	}
	
	
	// Returns as pitch, yaw, roll (Y,Z,X)
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	FRotator OpenRotation(0.f, OpenAngle, 0.f);
	GetOwner()->SetActorRotation(OpenRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

