// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "Action.h"


// Sets default values for this component's properties
UAction::UAction() : target(NULL), cost(1.0f), in_range(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAction::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAction::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UAction::AddPrecondition(std::string key, bool value)
{
	preconditions[key] = value;
}
void UAction::RemovePrecondition(std::string key)
{
	if (preconditions.find(key) != preconditions.end())
		preconditions.erase(key);
}
void UAction::AddEffect(std::string key, bool value)
{
	effects[key] = value;
}
void UAction::RemoveEffect(std::string key)
{
	if (effects.find(key) != effects.end())
		effects.erase(key);
}