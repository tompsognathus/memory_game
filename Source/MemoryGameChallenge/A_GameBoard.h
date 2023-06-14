// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_Card.h"
#include "A_GameBoard.generated.h"


UCLASS()
class MEMORYGAMECHALLENGE_API AA_GameBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_GameBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintImplementableEvent, Category="GameBoard")
	void UpdateNumGuessesUI(int NumGuesses);

	UFUNCTION(BlueprintCallable)
	void OnCardClicked(int CardId);

	UFUNCTION(BlueprintCallable)
	void ResetGame();

	UPROPERTY(EditAnywhere, Category="GameBoard")
	TArray<UBlueprint*> m_CardBlueprints;

	UPROPERTY(EditAnywhere, Category="GameBoard")
	USoundBase* m_CardMatchedSFX;

	UPROPERTY(EditAnywhere, Category = "GameBoard")
	USoundBase* m_VictorySFX;

	TArray<AActor*> m_CardsOnBoard;
	int m_BoardSize = 4;

private:
	void SpawnCards();
	void SpawnCard(int idx);
	void PositionCards();
	void ShuffleCards();
	void SetCardIds();
	FVector CalculateCardPosition(int CardIdx);
	bool CheckIfCardsMatch();
	int FindIdxOfCardWithCardId(int CardId);

	TArray<int> m_SelectedCardIdxs;
	int m_NumCardsMatched = 0;
	int m_NumGuesses = 0;
};
