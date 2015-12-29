// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "TakeWoodToContainer.h"
#include "WoodContainer.h"
#include "WoodCutter.h"

// Sets default values for this component's properties
UTakeWoodToContainer::UTakeWoodToContainer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	AddPrecondition("carrying_enough_wood", true); 
	AddEffect("container_has_wood", true);
	duration = 2;
	start_time = 0;
	fetched = false;
	cost = 5.0f;
}

// Called when the game starts
void UTakeWoodToContainer::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UTakeWoodToContainer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTakeWoodToContainer::reset()
{
	start_time = 0;
	fetched = false;
}

bool UTakeWoodToContainer::isDone()
{
	return fetched;
}

bool UTakeWoodToContainer::CheckProceduralPrecondition(AActor* agent)
{
	TActorIterator<AActor> it = TActorIterator<AActor>(GetWorld());
	for (; it; ++it)
	{
		TArray<UWoodContainer*> comps2;
		it->GetComponents(comps2);
		for (auto curr : comps2)
		{
			target = curr->GetOwner();
			return true;
		}
	}
	//for (TObjectIterator<UWoodContainer> Itr; Itr; ++Itr)
	//{
	//	target = Itr->GetOwner();
	//	return true;
	//}
	return false;
}

bool UTakeWoodToContainer::perform(AActor* agent)
{
	if (start_time == 0)
		start_time = World->GetTimeSeconds();
	if (World->GetTimeSeconds() - start_time >= duration)
	{
		TArray<UWoodCutter*> comps;
		agent->GetComponents(comps);
		for (auto ai : comps)
		{
			TArray<UWoodContainer*> comps2;
			target->GetComponents(comps2);
			ai->wood = 0;
			for (auto cnt : comps2)
				cnt->number_wood += 10;
		}
		fetched = true;
	}
	return true;
}



