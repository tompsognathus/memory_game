// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_CardMatcher.h"

// Sets default values for this component's properties
UAC_CardMatcher::UAC_CardMatcher()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_CardMatcher::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UAC_CardMatcher::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_CardMatcher::CompareCards(AActor* Card1, AActor* Card2)
{
	// check if the cards' tags match
	if (Card1->ActorHasTag(Card2->Tags[0]))
	{
		UE_LOG(LogTemp, Display, TEXT("Cards match!"));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Cards don't match!"));
	}
}

