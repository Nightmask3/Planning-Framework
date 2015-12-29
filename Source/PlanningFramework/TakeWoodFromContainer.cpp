// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "TakeWoodFromContainer.h"
#include "WoodContainer.h"
#include "Builder.h"

// Sets default values for this component's properties
UTakeWoodFromContainer::UTakeWoodFromContainer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	AddEffect("carrying_enough_wood", true);
	duration = 5;
	start_time = 0;
	fetched = false;
	cost = 1.0f;
}

// Called when the game starts
void UTakeWoodFromContainer::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UTakeWoodFromContainer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTakeWoodFromContainer::reset()
{
	start_time = 0;
	fetched = false;
}

bool UTakeWoodFromContainer::isDone()
{
	return fetched;
}

bool UTakeWoodFromContainer::CheckProceduralPrecondition(AActor* agent)
{
	TActorIterator<AActor> it = TActorIterator<AActor>(GetWorld());
	for (; it; ++it)
	{
		TArray<UWoodContainer*> comps2;
		it->GetComponents(comps2);
		for (auto curr : comps2)
		{
			if (curr->number_wood >= 10)
			{
				target = curr->GetOwner();
				return true;
			}
		}
	}
	//for (TObjectIterator<UWoodContainer> Itr; Itr; ++Itr)
	//{
	//	if (Itr->number_wood >= 10)
	//	{
	//		target = Itr->GetOwner();
	//		return true;
	//	}
	//}
	return false;
}

bool UTakeWoodFromContainer::perform(AActor* agent)
{
	if (start_time == 0)
		start_time = World->GetTimeSeconds();
	if (World->GetTimeSeconds() - start_time >= duration)
	{

		TArray<UBuilder*> comps;
		agent->GetComponents(comps);
		for (auto ai : comps)
		{
			ai->wood = 10;
			TArray<UWoodContainer*> comps2;
			target->GetComponents(comps2); 
			for (auto cnt : comps2)
			{
				cnt->number_wood -= 10;
			}
		}
		fetched = true;
	}
	return true;
}





