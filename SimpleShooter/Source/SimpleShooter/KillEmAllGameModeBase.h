// Copyright Cameron Davis 2021. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KillEmAllGameModeBase.generated.h"

UCLASS()
class SIMPLESHOOTER_API AKillEmAllGameModeBase : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
};
