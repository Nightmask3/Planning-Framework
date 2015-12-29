// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseGoap.h"
#include "Worker.generated.h"

/**
 * 
 */
UCLASS()
class PLANNINGFRAMEWORK_API UWorker : public UBaseGoap
{
	GENERATED_BODY()
	
	
public:

	// Sets default values for this component's properties
	UWorker();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void FailedToFindPlan(std::unordered_map<std::string, bool> goal);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 hunger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 food;

	float last_reduce_time;
};
