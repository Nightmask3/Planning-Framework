// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "GetPhoneNumberAction.h"
#include "PhoneNumber.h"
#include "TestAI.h"
#include "EngineUtils.h"


// Sets default values for this component's properties
UGetPhoneNumberAction::UGetPhoneNumberAction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	AddEffect("has_phone_number", true);
	duration = 10;
	start_time = 0;
	fetched = false;
	// ...
}


// Called when the game starts
void UGetPhoneNumberAction::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGetPhoneNumberAction::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}


void UGetPhoneNumberAction::reset()
{
	start_time = 0;
	fetched = false;
}

bool UGetPhoneNumberAction::isDone()
{
	return fetched;
}

bool UGetPhoneNumberAction::CheckProceduralPrecondition(AActor* agent)
{
	for (TObjectIterator<UPhoneNumber> Itr; Itr; ++Itr)
	{
		target = Itr->GetOwner();
		return true;
	}
	return false;
}

bool UGetPhoneNumberAction::perform(AActor* agent)
{
	if (start_time == 0)
		start_time = World->GetTimeSeconds();
	if (World->GetTimeSeconds() - start_time >= duration)
	{
		UActorComponent* s = agent->GetComponentByClass(UTestAI::StaticClass());
		UTestAI* ai = static_cast<UTestAI*>(s);
		if (ai)
		{
			ai->phone_number = true;
		}
		fetched = true;
	}
	return true;
}


