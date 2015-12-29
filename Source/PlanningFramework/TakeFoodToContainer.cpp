// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "TakeFoodToContainer.h"
#include "FoodContainer.h"
#include "Hunter.h"

// Sets default values for this component's properties
UTakeFoodToContainer::UTakeFoodToContainer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	AddPrecondition("carrying_enough_food", true);
	AddEffect("container_has_food", true);
	duration = 2;
	start_time = 0;
	fetched = false;
	cost = 5.0f;
}

// Called when the game starts
void UTakeFoodToContainer::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UTakeFoodToContainer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTakeFoodToContainer::reset()
{
	start_time = 0;
	fetched = false;
}

bool UTakeFoodToContainer::isDone()
{
	return fetched;
}

bool UTakeFoodToContainer::CheckProceduralPrecondition(AActor* agent)
{
	TActorIterator<AActor> it = TActorIterator<AActor>(GetWorld());
	for (; it; ++it)
	{
		TArray<UFoodContainer*> comps2;
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

bool UTakeFoodToContainer::perform(AActor* agent)
{
	if (start_time == 0)
		start_time = World->GetTimeSeconds();
	if (World->GetTimeSeconds() - start_time >= duration)
	{
		TArray<UHunter*> comps;
		agent->GetComponents(comps);
		for (auto ai : comps)
		{
			TArray<UFoodContainer*> comps2;
			target->GetComponents(comps2);
			ai->food -= 25;
			for (auto cnt : comps2)
				cnt->number_food += 25;
		}
		fetched = true;
	}
	return true;
}



