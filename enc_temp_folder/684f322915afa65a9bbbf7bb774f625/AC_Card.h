// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_Card.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEMORYGAMECHALLENGE_API UAC_Card : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_Card();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Card")
	void InitiateCardFlip();
		
private:
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
