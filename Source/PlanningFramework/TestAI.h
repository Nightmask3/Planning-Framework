// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "BaseGoap.h"
#include "TestAI.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLANNINGFRAMEWORK_API UTestAI : public UBaseGoap
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTestAI();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;


	std::unordered_map<std::string, bool> GetWorldState();
	std::unordered_map<std::string, bool> GetGoalState();
	void FailedToFindPlan(std::unordered_map<std::string, bool> goal);
	void PlanFound(std::unordered_map<std::string, bool> goal, std::queue<UAction*> actions);

	void ReachedGoal();
	void PlanAborted(UAction* aborter);
	bool MoveAgent(UAction* nextAction);
	
	int burritos;
	bool phone_number;
	
};
