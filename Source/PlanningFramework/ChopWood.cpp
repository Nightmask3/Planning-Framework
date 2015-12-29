// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "ChopWood.h"
#include "WoodCutter.h"
#include "TreeComponent.h"
#include "Animation/SkeletalMeshActor.h"
// Sets default values for this component's properties
UChopWood::UChopWood()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	AddEffect("carrying_enough_wood", true);
	duration = 10;
	start_time = 0;
	fetched = false;
	cost = 10.0f;
}

// Called when the game starts
void UChopWood::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UChopWood::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UChopWood::reset()
{
	start_time = 0;
	fetched = false;
}

bool UChopWood::isDone()
{
	return fetched;
}

bool UChopWood::CheckProceduralPrecondition(AActor* agent)
{
	TActorIterator<AActor> it = TActorIterator<AActor>(GetWorld());
	for (; it; ++it)
	{
		TArray<UTreeComponent*> comps2;
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

bool UChopWood::perform(AActor* agent)
{
	if (start_time == 0)
	{
		start_time = World->GetTimeSeconds();
		 TArray<USkeletalMeshComponent*> comps;
		agent->GetComponents(comps);
		for (auto ai : comps)
		{
			ai->GetAnimInstance()->Montage_Play(Montage);
		}

	}
	if (World->GetTimeSeconds() - start_time >= duration)
	{
		TArray<UWoodCutter*> comps;
		agent->GetComponents(comps);
		for (auto ai : comps)
		{
			ai->wood = 10;
		}

		TArray<UTreeComponent*> comps2;
		target->GetComponents(comps2);
		for (auto tree : comps2)
		{
			tree->wood -= 10;
			if (tree->wood == 0)
				target->Destroy();
		}

		fetched = true;
		in_range = false;
		TArray<USkeletalMeshComponent*> comps3;
		agent->GetComponents(comps3);
		for (auto it : comps3)
		{
			it->GetAnimInstance()->Montage_Stop(0.0f, Montage);
		}
	}
	return true;
}




