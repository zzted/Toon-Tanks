// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.h"
#include "PawnTurrent.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTurrent : public APawnBase
{
	GENERATED_BODY()
	
public:


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;
	

private:
	FTimerHandle FireRateTimerHandle;

	APawnTank* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 500.0f;

	void CheckFireCondition();
	
	float ReturnDistanceToPlayer();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
