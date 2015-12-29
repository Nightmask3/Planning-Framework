// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "Worker.h"

FVector move_here;
bool move_to_vector;
int rest_duration;
float rest_start;

// Sets default values for this component's properties
UWorker::UWorker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UWorker::BeginPlay()
{
	Super::BeginPlay();
	food = 0;
	hunger = 100;
	last_reduce_time = 0;

	move_to_vector = false;
	rest_start = 0;
	rest_duration = 0;
	// ...

}

// Called every frame
void UWorker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (last_reduce_time == 0)
		last_reduce_time = World->GetTimeSeconds();

	if (World->GetTimeSeconds() - last_reduce_time > 5)
	{
		hunger -= 10;
		if (hunger < 0)
			hunger = 0;
		last_reduce_time = World->GetTimeSeconds();
	}
	// ...
}


void UWorker::FailedToFindPlan(std::unordered_map<std::string, bool> goal)
{
	UE_LOG(LogTemp, Warning, TEXT("COULDNT FIND PLAN"));
	FVector loc = GetOwner()->GetActorLocation();
	if (!move_to_vector)
	{
		move_to_vector = true;
		move_here = FVector();
		int x = -1000 + (rand() % (2000));
		int y = -1000 + (rand() % (2000));
		move_here.X = x;
		move_here.Y = y;
		move_here.Z = loc.Z;
	}

	if (World->GetTimeSeconds() - rest_start < rest_duration)
	{

	}
	else
	if (move_to_vector)
	{
		APawn* p = static_cast<APawn*>(GetOwner());
		AController* controller = p->GetController();

		UNavigationSystem::SimpleMoveToLocation(controller, move_here);

		float dist = FVector::Dist(loc, move_here);

		float len = 50.0f;
		if (dist <= len)
		{
			move_to_vector = false;
			rest_start = World->GetTimeSeconds();
			rest_duration = 2 + rand() % 10;
		}
	}
}
