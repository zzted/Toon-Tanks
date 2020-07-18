// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/PawnTank.h"
#include "ToonTanks/PawnTurrent.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"


void ATankGameModeBase::BeginPlay() {
	Super::BeginPlay();

	HandleGameStart();
	
}

void ATankGameModeBase::HandleGameStart() {
	TargetTurrents = GetTargetTurrentCount();

	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	GameStart();

	if (PlayerControllerRef) {
		PlayerControllerRef->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;

		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);

		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}


void ATankGameModeBase::HandleGameOver(bool PlayerWon) {
	GameOver(PlayerWon);
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) {
	UE_LOG(LogTemp, Warning, TEXT("An Actor Died"));

	if (DeadActor == PlayerTank) {
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (PlayerControllerRef) {
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if(APawnTurrent* DestroyedTurrent = Cast<APawnTurrent>(DeadActor)){
		DestroyedTurrent->HandleDestruction();

		if (--TargetTurrents == 0) {
			HandleGameOver(true);
		}
	}
}

int32 ATankGameModeBase::GetTargetTurrentCount() {
	TArray<AActor*> TurrentActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurrent::StaticClass(), TurrentActors);
	return TurrentActors.Num();
}