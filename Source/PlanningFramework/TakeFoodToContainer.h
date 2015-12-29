// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Action.h"
#include "TakeFoodToContainer.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PLANNINGFRAMEWORK_API UTakeFoodToContainer : public UAction
{
	GENERATED_BODY()

public:
	UTakeFoodToContainer();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FString GetName() { return "Taking food to container..."; }

	void reset();
	bool isDone();
	bool CheckProceduralPrecondition(AActor* agent);
	bool perform(AActor* agent);

	float duration;
	float start_time;
	bool fetched;	
};
