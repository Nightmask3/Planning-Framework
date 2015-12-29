// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Action.h"
#include "OrderBurritoAction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLANNINGFRAMEWORK_API UOrderBurritoAction : public UAction
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOrderBurritoAction();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	FString GetName() { return "Order Burrito Action"; }
	void reset();
	bool isDone();
	bool CheckProceduralPrecondition(AActor* agent);
	bool perform(AActor* agent);

	float delivery_duration;
	float start_time;
	bool arrived;
};
