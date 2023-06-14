// Fill out your copyright notice in the Description page of Project Settings.


#include "A_GameBoard.h"

// Sets default values
AA_GameBoard::AA_GameBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AA_GameBoard::BeginPlay()
{
	Super::BeginPlay();
	SpawnCards();
	PositionCards();
	ShuffleCards();
}

// Called every frame
void AA_GameBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AA_GameBoard::SpawnCards()
{
	UE_LOG(LogTemp, Display, TEXT("Spawning cards"));
	int NumBlueprints = m_CardBlueprints.Num();
	if (NumBlueprints == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No card blueprints found. Did you forget to add them to the GameBoard?"));
		return;
	}

	for (int idx = 0; idx < NumBlueprints; idx++)
	{
		SpawnCard(idx);
		SpawnCard(idx);
	}
}

void AA_GameBoard::SpawnCard(int idx)
{
	// Spawn card twice
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* SpawnedCard = GetWorld()->SpawnActor<AActor>(m_CardBlueprints[idx]->GeneratedClass, SpawnParams);

	// Check if the card was successfully spawned
	if (SpawnedCard)
	{
		// Attach the spawned card to the game board
		SpawnedCard->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		// Add the card to the array of spawned cards
		m_CardsOnBoard.Add(SpawnedCard);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn card from blueprint %s"), *m_CardBlueprints[idx]->GetName());
	}
}

void AA_GameBoard::PositionCards()
{
	for (int idx = 0; idx < m_CardsOnBoard.Num(); idx++)
	{
		FVector NewPosition = CalculateCardPosition(idx);
		m_CardsOnBoard[idx]->SetActorLocation(NewPosition);
	}
}

void AA_GameBoard::ShuffleCards()
{
	m_CardsOnBoard.Sort([](const AActor& A, const AActor& B) {
		return FMath::FRand() < 0.5f;
	});

	PositionCards();
}

FVector AA_GameBoard::CalculateCardPosition(int CardIdx)
{
	int X = CardIdx % 4;
	int Y = CardIdx / 4;

	float XPosition = -450.0f + (X * 300.0f);
	float YPosition = -450.0f + (Y * 300.0f);

	return FVector(XPosition, YPosition, 100.0f);
}