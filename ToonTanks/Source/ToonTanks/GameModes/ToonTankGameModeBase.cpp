// Copyright Cameron Davis 2021 All Rights Reserved


#include "ToonTankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts
void AToonTankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTankGameModeBase::ActorDied(AActor* DeadActor)
{
	// Check what type of Actor die and either count up or lose game
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();

		if (--TargetTurrets == 0) 
		{
			HandleGameOver(true);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("A pawn has died"));
}

int32 AToonTankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	
	return TurretActors.Num();
}

void AToonTankGameModeBase::HandleGameStart()
{
	// Reference to the single player
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	TargetTurrets = GetTargetTurretCount();

	// Call the BP version of GameStart()
	GameStart();
}

void AToonTankGameModeBase::HandleGameOver(bool PlayerWon)
{
	// Call BP version of GameOver()
	GameOver(PlayerWon);
}

