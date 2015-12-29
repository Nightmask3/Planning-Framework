// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "Hunter.h"
#include "FoodContainer.h"
#include "Action.h"
#include "EngineUtils.h"

// Sets default values for this component's properties
UHunter::UHunter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHunter::BeginPlay()
{
	Super::BeginPlay();
	// ...
}

// Called every frame
void UHunter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

std::unordered_map<std::string, bool> UHunter::GetWorldState()
{
	std::unordered_map<std::string, bool> current_state;
	UFoodContainer* container = NULL;

	TActorIterator<AActor> it = TActorIterator<AActor>(GetWorld());
	for (; it; ++it)
	{
		TArray<UFoodContainer*> comps2;
		it->GetComponents(comps2);
		for (auto curr : comps2)
		{
			container = curr;
			break;
		}
		if (container)
			break;
	}
	//for (TObjectIterator<UWoodContainer> Itr; Itr; ++Itr)
	//{
	//	container = *Itr;
	//	break;
	//}
	int test = container->number_food;
	current_state["container_has_food"] = container->number_food >= 100;
	current_state["carrying_enough_food"] = food >= 10;
	current_state["not_hungry"] = hunger > 10;

	return current_state;
}

std::unordered_map<std::string, bool> UHunter::GetGoalState()
{
	std::unordered_map<std::string, bool> goal;

	goal["not_hungry"] = true;
	goal["container_has_food"] = true;

	return goal;
}


void UHunter::PlanFound(std::unordered_map<std::string, bool> goal, std::queue<UAction*> actions)
{
	UE_LOG(LogTemp, Warning, TEXT("FOUND A PLAN"));
}

void UHunter::ReachedGoal()
{
	UE_LOG(LogTemp, Warning, TEXT("REACHED GOAL"));
}

void UHunter::PlanAborted(UAction* aborter)
{
	UE_LOG(LogTemp, Warning, TEXT("Plan Aborted"));
}

bool UHunter::MoveAgent(UAction* nextAction)
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



