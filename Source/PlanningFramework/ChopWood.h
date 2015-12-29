// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Action.h"
#include "ChopWood.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PLANNINGFRAMEWORK_API UChopWood : public UAction
{
	GENERATED_BODY()
public:
	UChopWood();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FString GetName() { return "Chopping wood..."; }

	void reset();
	bool isDone();
	bool CheckProceduralPrecondition(AActor* agent);
	bool perform(AActor* agent);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anims")
		UAnimMontage *Montage;
	float duration;
	float start_time;
	bool fetched;
};
