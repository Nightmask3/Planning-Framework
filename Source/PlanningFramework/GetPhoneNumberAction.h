// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Action.h"
#include "GetPhoneNumberAction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLANNINGFRAMEWORK_API UGetPhoneNumberAction : public UAction
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGetPhoneNumberAction();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	FString GetName() { return "Get Phone Number Action"; }

	void reset();
	bool isDone();
	bool CheckProceduralPrecondition(AActor* agent);
	bool perform(AActor* agent);


	float duration;
	float start_time;
	bool fetched;
		
	
};
