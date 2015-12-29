// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "BuildAction.h"
#include "Builder.h"
#include "Wall.h"
#include "Animation/SkeletalMeshActor.h"

// Sets default values for this component's properties
UBuildAction::UBuildAction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	AddPrecondition("carrying_enough_wood", true);
	AddEffect("all_walls_built", true);
	duration = 10;
	start_time = 0;
	fetched = false;
	cost = 1.0f;
}

// Called when the game starts
void UBuildAction::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UBuildAction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBuildAction::reset()
{
	start_time = 0;
	fetched = false;
}

bool UBuildAction::isDone()
{
	return fetched;
}

bool UBuildAction::CheckProceduralPrecondition(AActor* agent)
{
	TActorIterator<AActor> it = TActorIterator<AActor>(GetWorld());
	for (; it; ++it)
	{
		TArray<UWall*> comps2;
		it->GetComponents(comps2);
		for (auto curr : comps2)
		{
			if (curr->size < 100)
			{
				target = curr->GetOwner();
				return true;
			}
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

bool UBuildAction::perform(AActor* agent)
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
		TArray<UBuilder*> comps;
		agent->GetComponents(comps);
		for (auto ai : comps)
		{
			TArray<UWall*> comps2;
			target->GetComponents(comps2);
			ai->wood = 0;

			for (auto wall : comps2)
			{
				wall->size += 10;

				AActor* actor = wall->GetOwner();

				TArray<UStaticMeshComponent*> comps3;
				actor->GetComponents(comps3);
				for (auto mesh : comps3)
				{
					FVector scale = mesh->GetComponentScale();
					scale.Z += 1;
					mesh->SetWorldScale3D(scale);
				}
			}
		}
		fetched = true;
		in_range = false;

		TArray<USkeletalMeshComponent*> comps3;
		agent->GetComponents(comps3);
		for (auto it : comps3)
		{
			it->GetAnimInstance()->Montage_Stop(0.0f, Montage);
		}
		// Every time a build action is performed, increment the counter
		counter++;
	}
	return true;
}



