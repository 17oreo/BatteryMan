// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan_GameMode.h"
#include "GameFramework/Actor.h"


ABatteryMan_GameMode::ABatteryMan_GameMode()
{
	PrimaryActorTick.bCanEverTick = true; //Enable ticking every frame
}

void ABatteryMan_GameMode::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABatteryMan_GameMode::SpawnPlayerRecharge, FMath::RandRange(2, 4), true); //Call SpawnPlayerRecharge every 2 to 5 seconds
}

void ABatteryMan_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//SpawnPlayerRecharge(); //Spawn a player recharge item
}

void ABatteryMan_GameMode::SpawnPlayerRecharge()
{
	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max); //Generate a random X coordinate within the specified range
	float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max); //Generate a random Y coordinate within the specified range

	FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z); //Create the spawn location vector

	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f); //No rotation

	GetWorld()->SpawnActor(PlayerRecharge, &SpawnPosition, &SpawnRotation); //Spawn the player recharge item at the generated location
}	


