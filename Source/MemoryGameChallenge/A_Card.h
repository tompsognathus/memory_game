// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_Card.generated.h"


UCLASS()
class MEMORYGAMECHALLENGE_API AA_Card : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_Card();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "Card")
	void InitiateCardFlip();
	void InitiateDelayedCardFlip();
	void SetWasMatched(bool WasMatched);

	void SetCardIdx(int CardId);
	int GetCardIdx();

	UPROPERTY(BlueprintReadOnly, Category = "Card")
	int m_CardId;

	UPROPERTY(BlueprintReadOnly, Category = "Card")
	bool m_CardWasMatched = false;

	UPROPERTY(BlueprintReadOnly, Category = "Card")
	bool m_CardIsFaceUp;

private:
	float m_DelayedFlipTimer = 0.f;
	bool m_PerformingDelayedFlip = false;
	void PerformDelayedFlip(float DeltaTime);


	bool m_IsRotating = false;

	void Rotate(float DeltaTime);

	// Rotation variables
	UPROPERTY(EditAnywhere, Category = "Card")
	float m_RotationSpeed = 100.f;

	float m_AngleRotated = 0.f;
	
	FRotator m_InitialRotation;
	FRotator m_TargetRotation;
	FRotator m_NewRotation;
};
