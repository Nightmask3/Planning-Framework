// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "TestAI.h"
#include "Action.h"

// Sets default values for this component's properties
UTestAI::UTestAI()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTestAI::BeginPlay()
{
	Super::BeginPlay();
	burritos = 0;
	phone_number = false;
	// ...
	
}

// Called every frame
void UTestAI::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

std::unordered_map<std::string, bool> UTestAI::GetWorldState()
{
	std::unordered_map<std::string, bool> current_state;
	current_state["has_burritos"] = burritos > 0;
	current_state["has_phone_number"] = phone_number;

	return current_state;
}

std::unordered_map<std::string, bool> UTestAI::GetGoalState()
{
	std::unordered_map<std::string, bool> goal;
	goal["has_burritos"] = true;

	return goal;
}

void UTestAI::FailedToFindPlan(std::unordered_map<std::string, bool> goal)
{
	UE_LOG(LogTemp, Warning, TEXT("COULDNT FIND PLAN"));
}

void UTestAI::PlanFound(std::unordered_map<std::string, bool> goal, std::queue<UAction*> actions)
{
	UE_LOG(LogTemp, Warning, TEXT("FOUND A PLAN"));
}

void UTestAI::ReachedGoal()
{
	UE_LOG(LogTemp, Warning, TEXT("REACHED GOAL"));
}

void UTestAI::PlanAborted(UAction* aborter)
{
	UE_LOG(LogTemp, Warning, TEXT("Plan Aborted"));
}

bool UTestAI::MoveAgent(UAction* nextAction)
{
	UE_LOG(LogTemp, Warning, TEXT("MOVING"));

	float step = World->DeltaTimeSeconds *2 ;
	FVector loc =  GetOwner()->GetActorLocation();
	
	float dist = FVector::Dist(loc, nextAction->target->GetActorLocation());

	if (dist <= 150.0f)
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

