// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

class AActor;
class USceneComponent;

/**
 * 
 */
UCLASS()
class ROCKINGKNIGHT_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Game", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static bool IsOnScreen(const UObject* WorldContextObject, FVector const Location, int32 PlayerIndex = 0);

	UFUNCTION(BlueprintPure, Category = "Game", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static bool IsCompnoentOnScreen(const UObject* WorldContextObject, USceneComponent* Component, int32 PlayerIndex = 0);

	UFUNCTION(BlueprintPure, Category = "Game", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static bool IsActorOnScreen(const UObject* WorldContextObject, AActor* Actor, int32 PlayerIndex = 0);

};
