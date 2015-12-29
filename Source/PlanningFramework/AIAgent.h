// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Planner.h"
#include <set>
#include <queue>
#include <string>
#include "AIAgent.generated.h"


enum STATE
{
	IDLE,
	ACTION,
	MOVE
};

class UAction;
class UBaseGoap;
class AAICharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PLANNINGFRAMEWORK_API UAIAgent : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UAIAgent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void IdleState();
	void ActionState();
	void MoveState();
	void AddAction(UAction* a);

	UAction* GetAction(int action);
	void RemoveAction(UAction* action);
	bool HasPlan();

	int current_state;

	Planner goap_planner;
	UBaseGoap* provider;
	std::set<UAction*> available_actions;
	std::queue<UAction*> current_actions;
	AAICharacter* character;
};
