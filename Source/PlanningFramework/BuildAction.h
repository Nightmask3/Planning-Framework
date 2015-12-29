// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Action.h"
#include "BuildAction.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PLANNINGFRAMEWORK_API UBuildAction : public UAction
{
	GENERATED_BODY()
public:
	UBuildAction();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FString GetName() { return "Building Wall..."; }

	void reset();
	bool isDone();
	bool CheckProceduralPrecondition(AActor* agent);
	bool perform(AActor* agent);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anims")
		UAnimMontage *Montage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Build Info")
		uint8 counter = 0;
	float duration;
	float start_time;
	bool fetched;
};
