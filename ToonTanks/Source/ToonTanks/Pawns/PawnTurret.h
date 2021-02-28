// Copyright Cameron Davis 2021 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

private:
	
	APawnTank* PlayerPawn;
	FTimerHandle FireRateTimerHandle;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRate = 2.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRange = 500.f;

	void CheckFireCondition();
	float ReturnDistanceToPlayer();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
