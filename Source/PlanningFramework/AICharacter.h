// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include <string>
#include "AICharacter.generated.h"

UCLASS(Blueprintable, BlueprintType)
class PLANNINGFRAMEWORK_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CurrentAction)
	int32 balls;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CurrentAction)
	FString current_action;
};
