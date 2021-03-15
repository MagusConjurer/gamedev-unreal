// Copyright Cameron Davis 2021. All Rights Reserved.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	// Get the owning pawn and it's controller
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) { return; }
	AController* OwnerController = OwnerPawn->GetController();
	if (!OwnerController) { return; }

	// Get location and rotation of the controller using out parameters
	FVector ViewpointLocation;
	FRotator ViewpointRotation;
	OwnerController->GetPlayerViewPoint(ViewpointLocation, ViewpointRotation);

	// Set the range and get any hit on the Bullet trace channel
	FVector LineTraceEnd = ViewpointLocation + ViewpointRotation.Vector() * MaxRange;
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, ViewpointLocation, LineTraceEnd, ECollisionChannel::ECC_GameTraceChannel1);
	
	if (HitResult.bBlockingHit)
	{
		FVector ShotDirection = -ViewpointRotation.Vector();
		// Show where bullet hits
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletImpact, HitResult.Location, ShotDirection.Rotation());
		
		// Get what was hit and send damage
		AActor* HitActor = HitResult.GetActor();
		if (HitActor) 
		{ 
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

