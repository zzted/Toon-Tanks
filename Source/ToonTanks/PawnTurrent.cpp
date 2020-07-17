// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurrent.h"
#include "Kismet/GameplayStatics.h"

void APawnTurrent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurrent::CheckFireCondition, FireRate, true, false);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

}

// Called every frame
void APawnTurrent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange) return;

	RotateTurrent(PlayerPawn->GetActorLocation());
}

void APawnTurrent::CheckFireCondition() {
	//If Player is valid
	if (!PlayerPawn) return;
	//If Player is in range
	if (ReturnDistanceToPlayer() <= FireRange) {
		Fire();
	}
}

float APawnTurrent::ReturnDistanceToPlayer() {
	if (!PlayerPawn) return 0.0f;
	float Distance = ((PlayerPawn->GetActorLocation() - GetActorLocation()).Size());
	return Distance;
}

void APawnTurrent::HandleDestruction() {
	Super::HandleDestruction();
}
