// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/EngineTypes.h"
#include "Knight.generated.h"

class UStaticMeshComponent;
class AProjectile;
class USoundBase;

UCLASS()
class ROCKINGKNIGHT_API AKnight : public APawn
{
	GENERATED_BODY()

public:

	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;	


	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent * MeshComp;
	
	UPROPERTY(EditAnywhere, Category="Speed")
	float MoveSpeed = 100.f;

	UPROPERTY(EditAnywhere, Category = "Gun")
	float FireRate = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Game")
	float OutOfScrenElapsedTime = 0.f;
	
	UPROPERTY(EditAnywhere, Category = "Game")
	float MaxTimeOutOfScreen = 2.f;

	UPROPERTY(EditAnywhere, Category = "Gun")
	FVector GunOffset = FVector(60.f,0.f,0.f);

	UPROPERTY(EditAnywhere, Category = "Gun")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Gun")
	USoundBase* FireSound;

	FTimerHandle TimerHandle;

private:

	bool bCanIShoot = true;
	
public:
	// Sets default values for this pawn's properties
	AKnight();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TryShoot();

	void SetICanShootAgain();
};
