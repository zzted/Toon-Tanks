// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"



void ATankGameModeBase::BeginPlay() {


	
}

void ATankGameModeBase::HandleGameStart() {

}


void ATankGameModeBase::HandleGameOver(bool PlayerWon) {

}

void ATankGameModeBase::ActorDied(AActor* DeadActor) {
	UE_LOG(LogTemp, Warning, TEXT("An Actor Died"));
}