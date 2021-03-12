// Copyright Cameron Davis 2021 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

// Forward declarations

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()

public:

	APawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Play effects and handle destruction of pawn
	virtual void HandleDestruction() override;

	bool GetIsPlayerAlive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* Camera;

	FVector MoveDirection;
	FQuat RotationDirection;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 100.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed = 100.f;

	APlayerController* PlayerControllerRef;
	bool bIsPlayerAlive = true;

	void CalcualateMoveInput(float Value);
	void CalculateRotateInput(float Value);
	void Move();
	void Rotate();
};
