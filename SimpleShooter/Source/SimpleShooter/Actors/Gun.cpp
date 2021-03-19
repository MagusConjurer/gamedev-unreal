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

// Get the owning pawn and it's controller
AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) { return nullptr; }
	return OwnerPawn->GetController();
}

bool AGun::GunTrace(FHitResult& HitResult, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (!OwnerController) { return false; }

	// Get location and rotation of the controller using out parameters
	FVector ViewpointLocation;
	FRotator ViewpointRotation;
	OwnerController->GetPlayerViewPoint(ViewpointLocation, ViewpointRotation);

	// Set the range and direction
	FVector LineTraceEnd = ViewpointLocation + ViewpointRotation.Vector() * MaxRange;
	ShotDirection = -ViewpointRotation.Vector();
	
	// Ignore collision for the gun and the character holding it
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(HitResult, ViewpointLocation, LineTraceEnd, ECollisionChannel::ECC_GameTraceChannel1, Params);
}


void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult HitResult;
	FVector ShotDirection;
	bool bSuccess = GunTrace(HitResult, ShotDirection);
	
	if (bSuccess)
	{
		// Show where bullet hits
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletImpact, HitResult.Location, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), BulletImpactSound, HitResult.Location, ShotDirection.Rotation());
		
		// Get what was hit and send damage
		AActor* HitActor = HitResult.GetActor();
		if (HitActor) 
		{ 
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			AController* OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

