// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_Card.h"

// Sets default values for this component's properties
UAC_Card::UAC_Card()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	m_InitialRotation = FRotator(0.f, 0.f, 0.f);
	m_TargetRotation = FRotator(180.f, 0.f, 0.f);
}


// Called when the game starts
void UAC_Card::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void UAC_Card::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_IsRotating)
	{
		Rotate(DeltaTime);
	}

}

void UAC_Card::InitiateCardFlip()
{
	m_IsRotating = true;
}

void UAC_Card::Rotate(float DeltaTime)
{
	m_AngleRotated += m_RotationSpeed * DeltaTime;

	m_NewRotation = m_InitialRotation + FRotator(0.f, 0.f,  m_AngleRotated);

	// Stop rotating if we're close enough to target rotation and snap to it
	m_IsRotating = FMath::Abs(FMath::Abs(m_AngleRotated) - 180.f) > FMath::Abs(m_RotationSpeed * 0.02);
	if (!m_IsRotating)
	{
		// Snap to target rotation
		m_NewRotation = m_TargetRotation;
		// Set up for next flip
		m_AngleRotated = 0.f;
		m_TargetRotation = m_InitialRotation;
		m_InitialRotation = m_NewRotation;
	}
	// Rotate
	GetOwner()->SetActorRotation(m_NewRotation);
}