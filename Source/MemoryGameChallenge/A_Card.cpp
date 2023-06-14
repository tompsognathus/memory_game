// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Card.h"

// Sets default values
AA_Card::AA_Card()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AA_Card::BeginPlay()
{
	Super::BeginPlay();

	// Make card face down
	SetActorRotation(FRotator(0.f, 0.f, 180.f));
	m_CardIsFaceUp = false;
}

// Called every frame
void AA_Card::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_IsRotating)
	{
		Rotate(DeltaTime);
	}
	if (m_PerformingDelayedFlip)
	{
		PerformDelayedFlip(DeltaTime);
	}
}

void AA_Card::InitiateCardFlip()
{
	m_IsRotating = true;
	if (m_CardIsFaceUp)
	{
		m_InitialRotation = FRotator(0.f, 0.f, 0.f);
		m_TargetRotation = FRotator(0.f, 0.f, 180.f);
	}
	else
	{
		m_InitialRotation = FRotator(0.f, 0.f, 180.f);
		m_TargetRotation = FRotator(0.f, 0.f, 0.f);
	}
	m_CardIsFaceUp = !m_CardIsFaceUp;
}

void AA_Card::InitiateDelayedCardFlip()
{
	m_DelayedFlipTimer = 1.f;
	m_PerformingDelayedFlip = true;
}



void AA_Card::SetWasMatched(bool WasMatched)
{
	m_CardWasMatched = WasMatched;
}


void AA_Card::PerformDelayedFlip(float DeltaTime)
{
	if (m_DelayedFlipTimer > 0.f)
	{
		m_DelayedFlipTimer -= DeltaTime;
	}
	else
	{
		InitiateCardFlip();
		m_PerformingDelayedFlip = false;
	}
}

void AA_Card::Rotate(float DeltaTime)
{
	m_AngleRotated += m_RotationSpeed * DeltaTime;

	m_NewRotation = m_InitialRotation + FRotator(0.f, 0.f, m_AngleRotated);

	// Stop rotating if we're close enough to target rotation and snap to it
	m_IsRotating = FMath::Abs(FMath::Abs(m_AngleRotated) - 180.f) > FMath::Abs(m_RotationSpeed * 0.02);
	if (!m_IsRotating)
	{
		// Snap to target rotation
		m_NewRotation = m_TargetRotation;
		// Set up for next flip
		m_AngleRotated = 0.f;
	}
	// Rotate
	SetActorRotation(m_NewRotation);
}

void AA_Card::SetCardIdx(int CardId)
{
	m_CardId = CardId;
}

int AA_Card::GetCardIdx()
{
	return m_CardId;
}


