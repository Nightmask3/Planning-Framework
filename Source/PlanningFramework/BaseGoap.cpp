// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "BaseGoap.h"

//
//// Sets default values for this component's properties
//UBaseGoap::UBaseGoap()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	bWantsBeginPlay = true;
//	PrimaryComponentTick.bCanEverTick = true;
//
//	// ...
//}


// Called when the game starts
void UBaseGoap::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseGoap::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

