// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RockingKnightGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ROCKINGKNIGHT_API URockingKnightGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LevelSpeed")
	FVector LevelSpeed;


};
