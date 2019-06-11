// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"

bool UMyBlueprintFunctionLibrary::IsOnScreen(const UObject* WorldContextObject, FVector const Location, int32 PlayerIndex /*= 0*/)
{
	FVector2D MyScreenLocation;
	UGameplayStatics::ProjectWorldToScreen(UGameplayStatics::GetPlayerController(WorldContextObject, PlayerIndex), Location, MyScreenLocation);
	
	FVector2D MyScreenSize;
	GEngine->GameViewport->GetViewportSize(MyScreenSize);

	FVector2D const Result = MyScreenSize - MyScreenLocation;

	return FMath::IsWithin(Result, FVector2D::ZeroVector, MyScreenSize);
}

bool UMyBlueprintFunctionLibrary::IsCompnoentOnScreen(const UObject* WorldContextObject, USceneComponent* Component, int32 PlayerIndex /*= 0*/)
{
	if (Component)
	{
		return IsOnScreen(WorldContextObject, Component->GetComponentLocation(), PlayerIndex);
	}
	return false;
}

bool UMyBlueprintFunctionLibrary::IsActorOnScreen(const UObject* WorldContextObject, AActor* Actor, int32 PlayerIndex /*= 0*/)
{
	if (Actor)
	{
		return IsOnScreen(WorldContextObject, Actor->GetActorLocation(), PlayerIndex);
	}
	return false;
}
