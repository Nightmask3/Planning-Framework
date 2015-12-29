// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Action.h"
#include "TakeFoodFromContainer.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PLANNINGFRAMEWORK_API UTakeFoodFromContainer : public UAction
{
	GENERATED_BODY()

public:
	UTakeFoodFromContainer();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FString GetName() { return "Taking food from container..."; }

	void reset();
	bool isDone();
	bool CheckProceduralPrecondition(AActor* agent);
	bool perform(AActor* agent);

	float duration;
	float start_time;
	bool fetched;
};
