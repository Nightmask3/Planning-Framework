// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "TakeFoodFromContainer.h"
#include "FoodContainer.h"
#include "Worker.h"

// Sets default values for this component's properties
UTakeFoodFromContainer::UTakeFoodFromContainer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	AddEffect("carrying_enough_food", true);
	duration = 5;
	start_time = 0;
	fetched = false;
	cost = 1.0f;
}

// Called when the game starts
void UTakeFoodFromContainer::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UTakeFoodFromContainer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTakeFoodFromContainer::reset()
{
	start_time = 0;
	fetched = false;
}

bool UTakeFoodFromContainer::isDone()
{
	return fetched;
}

bool UTakeFoodFromContainer::CheckProceduralPrecondition(AActor* agent)
{
	TActorIterator<AActor> it = TActorIterator<AActor>(GetWorld());
	for (; it; ++it)
	{
		TArray<UFoodContainer*> comps2;
		it->GetComponents(comps2);
		for (auto curr : comps2)
		{
			if (curr->number_food >= 10)
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

bool UTakeFoodFromContainer::perform(AActor* agent)
{
	if (start_time == 0)
		start_time = World->GetTimeSeconds();
	if (World->GetTimeSeconds() - start_time >= duration)
	{

		TArray<UWorker*> comps;
		agent->GetComponents(comps);
		for (auto ai : comps)
		{
			ai->food = 10;
			TArray<UFoodContainer*> comps2;
			target->GetComponents(comps2);
			for (auto cnt : comps2)
			{
				cnt->number_food -= 10;
			}
		}
		fetched = true;
	}
	return true;
}






