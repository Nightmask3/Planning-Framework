// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "AIAgent.h"
#include "Action.h"
#include "BaseGoap.h"
#include <unordered_map>
#include <string>
#include "AICharacter.h"

// Sets default values for this component's properties
UAIAgent::UAIAgent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

// Called when the game starts
void UAIAgent::BeginPlay()
{
	Super::BeginPlay();
	current_state = STATE::IDLE;
	AActor* actor = GetOwner();
	character = static_cast<AAICharacter*>(actor);

	// populate agent data
	for (UActorComponent* i : actor->GetComponents())
	{
		UBaseGoap* goap = dynamic_cast<UBaseGoap*>(i);
		if (goap)
		{

			UE_LOG(LogTemp, Warning, TEXT("FOUND BASE GOAP"));
			provider = goap;
		}
		else
		{
			UAction* action = dynamic_cast<UAction*> (i);
			if (action)
				available_actions.insert(action);
		}
	}
	// ...
	
}

// Called every frame
void UAIAgent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if (!provider)
		return;
	switch (current_state)
	{
	case STATE::IDLE:
		IdleState();
		break;
	case STATE::ACTION:
		ActionState();
		break;
	case STATE::MOVE:
		MoveState();
		break;
	}
}

void UAIAgent::IdleState()
{
	std::unordered_map<std::string, bool> state = provider->GetWorldState();
	std::unordered_map<std::string, bool> goal = provider->GetGoalState();

	character->current_action = "Idle";

	std::queue<UAction*> plan = goap_planner.Plan(GetOwner(), available_actions, state, goal);
	if (plan.size() > 0) {
		current_actions = plan;
		provider->PlanFound(goal, plan);

		current_state = STATE::ACTION;
	}
	else 
	{
		provider->FailedToFindPlan(goal);
	}
}

void UAIAgent::ActionState()
{
	if (!HasPlan())
	{
		provider->ReachedGoal();
		current_state = STATE::IDLE;
	}
	UAction* action = current_actions.front();
	if (action->isDone()) 
	{
		current_actions.pop();
	}
	if (HasPlan()) 
	{
		action = current_actions.front();
		character->current_action = action->GetName();
		bool inRange = action->MoveToTarget()? action->IsInRange() : true;

		if (inRange) {
			bool success = action->perform(GetOwner());

			if (!success) {
				current_state = STATE::IDLE;
				provider->PlanAborted(action);
			}
		}
		else 
		{
			current_state = STATE::MOVE;
		}

	}
	else 
	{
		current_state = STATE::IDLE;
		provider->ReachedGoal();
	}
}

void UAIAgent::MoveState()
{
	UAction* action = current_actions.front();
	if (action->MoveToTarget() && action->target == NULL)
	{
		current_state = STATE::IDLE;
		return;
	}

	// get the agent to move itself
	if (provider->MoveAgent(action)) 
	{
		current_state = STATE::ACTION;
	}
}

void UAIAgent::AddAction(UAction* a) 
{
	available_actions.insert(a);
}

UAction* UAIAgent::GetAction(int action) 
{
	return NULL;
}

void UAIAgent::RemoveAction(UAction* action) 
{
	//available_actions.delet;
}

bool UAIAgent::HasPlan() 
{
	return current_actions.size() > 0;
}


