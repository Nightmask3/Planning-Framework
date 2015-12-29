// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "Builder.h"
#include "Wall.h"
#include "Action.h"
#include "EngineUtils.h"

// Sets default values for this component's properties
UBuilder::UBuilder()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UBuilder::BeginPlay()
{
	Super::BeginPlay();
	wood = 0;
	hunger = 100;
	// ...

}

// Called every frame
void UBuilder::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

std::unordered_map<std::string, bool> UBuilder::GetWorldState()
{
	std::unordered_map<std::string, bool> current_state;
	UWall* container = NULL;

	TActorIterator<AActor> it = TActorIterator<AActor>(GetWorld());
	for (; it; ++it)
	{
		TArray<UWall*> comps2;
		it->GetComponents(comps2);
		for (auto curr : comps2)
		{
			if (curr->size < 100)
			{
				container = curr;
				break;
			}
		}
		if (container)
			break;
	}

	/*for (TObjectIterator<UWall> Itr; Itr; ++Itr)
	{
		
		if (Itr->size < 100)
			container = *Itr;
		break;
	}*/

	current_state["all_walls_built"] = container == NULL;
	current_state["carrying_enough_wood"] = wood == 10;
	current_state["not_hungry"] = hunger > 10;

	return current_state;
}

std::unordered_map<std::string, bool> UBuilder::GetGoalState()
{
	std::unordered_map<std::string, bool> goal;

	goal["not_hungry"] = true;
	goal["all_walls_built"] = true;

	return goal;
}

void UBuilder::PlanFound(std::unordered_map<std::string, bool> goal, std::queue<UAction*> actions)
{
	UE_LOG(LogTemp, Warning, TEXT("FOUND A PLAN"));
}

void UBuilder::ReachedGoal()
{
	UE_LOG(LogTemp, Warning, TEXT("REACHED GOAL"));
}

void UBuilder::PlanAborted(UAction* aborter)
{
	UE_LOG(LogTemp, Warning, TEXT("Plan Aborted"));
}

bool UBuilder::MoveAgent(UAction* nextAction)
{
	UE_LOG(LogTemp, Warning, TEXT("MOVING"));

	float step = World->DeltaTimeSeconds * 2;
	FVector loc = GetOwner()->GetActorLocation();

	float dist = FVector::Dist(loc, nextAction->target->GetActorLocation());

	float len = nextAction->target->GetActorScale3D().Size() / 2.0f + 550;
	if (dist <= len)
	{
		nextAction->SetInRange(true);
		return true;
	}
	//FVector new_loc = FMath::Lerp(loc, nextAction->target->GetActorLocation(), step);

	//GetOwner()->SetActorLocation(new_loc);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("condition is true")));
	APawn* p = static_cast<APawn*>(GetOwner());
	AController* controller = p->GetController();

	UNavigationSystem::SimpleMoveToLocation(controller, nextAction->target->GetActorLocation());

	return false;
}



