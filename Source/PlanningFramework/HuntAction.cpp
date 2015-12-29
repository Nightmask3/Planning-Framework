// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "HuntAction.h"
#include "Hunter.h"
#include "AnimalComponent.h"

// Sets default values for this component's properties
UHuntAction::UHuntAction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	AddEffect("carrying_enough_food", true);
	duration = 10;
	start_time = 0;
	fetched = false;
	cost = 10.0f;
}

// Called when the game starts
void UHuntAction::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UHuntAction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHuntAction::reset()
{
	start_time = 0;
	fetched = false;
}

bool UHuntAction::isDone()
{
	return fetched;
}

bool UHuntAction::CheckProceduralPrecondition(AActor* agent)
{
	TActorIterator<AActor> it = TActorIterator<AActor>(GetWorld());
	for (; it; ++it)
	{
		TArray<UAnimalComponent*> comps2;
		it->GetComponents(comps2);
		for (auto curr : comps2)
		{
			target = curr->GetOwner();
			return true;
		}
	}
	//for (TObjectIterator<UPhoneNumber> Itr; Itr; ++Itr)
	//{
	//	target = Itr->GetOwner();
	//	return true;
	//}
	return false;
}

bool UHuntAction::perform(AActor* agent)
{
	if (start_time == 0)
		start_time = World->GetTimeSeconds();
	if (World->GetTimeSeconds() - start_time >= duration)
	{
		TArray<UHunter*> comps;
		agent->GetComponents(comps);
		for (auto ai : comps)
		{
			ai->food += 30;
		}

		//TArray<UAnimalComponent*> comps2;
		//target->GetComponents(comps2);
		//for (auto tree : comps2)
		//{
		//	tree->wood -= 10;
		//	if (tree->wood == 0)
		target->Destroy();
	/*	}*/

		fetched = true;
	}
	return true;
}




