// Copyright Cameron Davis 2021. All Rights Reserved.


#include "KillEmAllGameModeBase.h"

void AKillEmAllGameModeBase::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController)
	{
		PlayerController->GameHasEnded(nullptr, false);
	}

	UE_LOG(LogTemp, Warning, TEXT("%s has died."), *PawnKilled->GetName())
}