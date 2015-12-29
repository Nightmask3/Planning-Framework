// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include <unordered_map>
#include <string>
#include <queue>
#include "Action.generated.h"

class AActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLANNINGFRAMEWORK_API UAction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAction();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual bool MoveToTarget() { return true; }

	 void ResetAction() {
		in_range = false;
		target = NULL;
		reset();
	}

	virtual void reset() {}
	virtual bool isDone() { return true; }
	virtual bool CheckProceduralPrecondition(AActor* agent) { return true; }
	virtual bool perform(AActor* agent) { return false; }
	virtual FString GetName() { return "Generic Action"; }

	bool IsInRange() {
		return in_range;
	}

	void SetInRange(bool val) {
		in_range = val;
	}

	void AddPrecondition(std::string key, bool value);
	void RemovePrecondition(std::string key);
	void AddEffect(std::string key, bool value);
	void RemoveEffect(std::string key);
		
	AActor* target;

	std::unordered_map<std::string, bool> preconditions;
	std::unordered_map<std::string, bool> effects;
	float cost;
	bool in_range;

};
