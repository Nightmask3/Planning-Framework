// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include <unordered_map>
#include <string>
#include <queue>
#include "BaseGoap.generated.h"

class UAction;

//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS(ClassGroup = (Custom), abstract)
class PLANNINGFRAMEWORK_API UBaseGoap : public UActorComponent
{
	GENERATED_BODY()

public:	
	//// Sets default values for this component's properties
	//UBaseGoap();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual std::unordered_map<std::string, bool> GetWorldState() { return std::unordered_map<std::string, bool>(); }
	virtual std::unordered_map<std::string, bool> GetGoalState() { return std::unordered_map<std::string, bool>(); }
	virtual void FailedToFindPlan(std::unordered_map<std::string, bool> goal){}
	virtual void PlanFound(std::unordered_map<std::string, bool> goal, std::queue<UAction*> actions){}

	virtual void ReachedGoal() {}
	virtual void PlanAborted(UAction* aborter) {}
	virtual bool MoveAgent(UAction* nextAction) { return false; }
	
};
