// Copyright Cameron Davis 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* Input = nullptr;

	void Grab();
	void Release();
	void GetPhysicsHandle();
	void SetupInputComponent();

	// Return the line trace end
	FVector GetLineTraceEnd() const;

	// Return the player's location in the world
	FVector GetPlayerPosition() const;

	// Return first actor within reach with a physics body
	FHitResult GetFirstPhysicsBodyInReach() const;
	
};
