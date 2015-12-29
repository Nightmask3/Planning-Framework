// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "OrderBurritoAction.h"
#include "PhoneComponent.h"
#include "TestAI.h"
#include "EngineUtils.h"

// Sets default values for this component's properties
UOrderBurritoAction::UOrderBurritoAction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	AddPrecondition("has_phone_number", true);
	AddEffect("has_burritos", true);
	delivery_duration = 2;
	start_time = 0;
	arrived = false;
	// ...
}


// Called when the game starts
void UOrderBurritoAction::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOrderBurritoAction::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UOrderBurritoAction::reset() 
{
	start_time = 0;
	arrived = false;
}

bool UOrderBurritoAction::isDone() 
{ 
	return arrived; 
}

bool UOrderBurritoAction::CheckProceduralPrecondition(AActor* agent) 
{ 
	for (TObjectIterator<UPhoneComponent> Itr; Itr; ++Itr)
	{
		target = Itr->GetOwner();
		return true;
	}
	return false; 
}

bool UOrderBurritoAction::perform(AActor* agent) 
{ 
	if (start_time == 0)
		start_time = World->GetTimeSeconds();
	if(World->GetTimeSeconds() - start_time >= delivery_duration)
	{
		UActorComponent* s = agent->GetComponentByClass(UTestAI::StaticClass());
		UTestAI* ai = static_cast<UTestAI*>(s);
		if (ai)
		{
			ai->burritos = 1;
		}
		arrived = true;
	}
	return true; 
}

