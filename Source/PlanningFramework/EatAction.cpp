// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "EatAction.h"
#include "Worker.h"
#include "Wall.h"
#include "PhoneComponent.h"

// Sets default values for this component's properties
UEatAction::UEatAction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	AddPrecondition("carrying_enough_food", true);
	AddEffect("not_hungry", true);
	duration = 5;
	start_time = 0;
	finished = false;
	cost = 1.0f;
}

// Called when the game starts
void UEatAction::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UEatAction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEatAction::reset()
{
	start_time = 0;
	finished = false;
}

bool UEatAction::isDone()
{
	return finished;
}

bool UEatAction::CheckProceduralPrecondition(AActor* agent)
{
	TActorIterator<AActor> it = TActorIterator<AActor>(GetWorld());
	for (; it; ++it)
	{
		TArray<UPhoneComponent*> comps2;
		it->GetComponents(comps2);
		for (auto curr : comps2)
		{
			target = curr->GetOwner();
			return true;
		}
	}
	//for (TObjectIterator<UWall> Itr; Itr; ++Itr)
	//{
	//	if (Itr->size < 100)
	//	{
	//		target = Itr->GetOwner();
	//		return true;
	//	}
	//}
	return false;
}

bool UEatAction::perform(AActor* agent)
{
	if (start_time == 0)
		start_time = World->GetTimeSeconds();

	if (World->GetTimeSeconds() - start_time >= duration)
	{
		TArray<UWorker*> comps;
		agent->GetComponents(comps);
		for (auto ai : comps)
		{
			ai->food -= 10;
			ai->hunger += 50;
		}
		finished = true;
	}
	return true;
}



