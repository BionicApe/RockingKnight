// Fill out your copyright notice in the Description page of Project Settings.


#include "Knight.h"
#include "Components/StaticMeshComponent.h"
#include "RockingKnightGameInstance.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "TimerManager.h"

const FName AKnight::MoveForwardBinding("MoveForward");
const FName AKnight::MoveRightBinding("MoveRight");
const FName AKnight::FireForwardBinding("FireForward");
const FName AKnight::FireRightBinding("FireRight");


// Sets default values
AKnight::AKnight()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComp;
}

void AKnight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis(MoveForwardBinding);
		PlayerInputComponent->BindAxis(MoveRightBinding);
		PlayerInputComponent->BindAxis(FireForwardBinding);
		PlayerInputComponent->BindAxis(FireRightBinding);
	}
}

// Called every frame
void AKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float MoveForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float MoveRightValue = GetInputAxisValue(MoveRightBinding);
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);

	URockingKnightGameInstance* GI = GetGameInstance<URockingKnightGameInstance>();
	const FVector LevelMovement = GI->LevelSpeed * DeltaTime;

	const FVector MoveDirection = FVector(MoveForwardValue, MoveRightValue, 0.f);
	const FVector IntendedMovement = (MoveDirection * DeltaTime * MoveSpeed) + LevelMovement;

	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);
	const FRotator FireRotation = FireDirection.Rotation();

	const FVector IntendedLocation = IntendedMovement + GetActorLocation();

	const FVector FinalLocation = UMyBlueprintFunctionLibrary::IsOnScreen(GetWorld(), IntendedLocation) ? IntendedMovement : LevelMovement;


	FHitResult Hit;

	RootComponent->MoveComponent(FinalLocation, FireRotation, true, &Hit);

	if (Hit.IsValidBlockingHit())
	{
		FVector Deflection = FVector::VectorPlaneProject(FinalLocation, Hit.Normal.GetSafeNormal2D()) * (1.f - Hit.Time);
		RootComponent->MoveComponent(Deflection, FireRotation, true);
	}
	if (FireDirection.SizeSquared() > 0.f)
	{
		TryShoot();
	}

	if (!UMyBlueprintFunctionLibrary::IsOnScreen(GetWorld(), GetActorLocation()))
	{
		OutOfScrenElapsedTime+= DeltaTime;
		if (OutOfScrenElapsedTime > MaxTimeOutOfScreen)
		{
			Destroy();
		}
	}
	else {
		OutOfScrenElapsedTime = 0.f;
	}

}

void AKnight::TryShoot()
{
	if (bCanIShoot)
	{

		FRotator const Rotation = RootComponent->GetComponentRotation();
		const FVector SpawnLocation = GetActorLocation() + Rotation.RotateVector(GunOffset);

		if (UWorld* const World = GetWorld())
		{
			World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, Rotation);
			bCanIShoot = false;
			World->GetTimerManager().SetTimer(TimerHandle, this, &AKnight::SetICanShootAgain, FireRate);

			if (FireSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, SpawnLocation);
			}
		}
	}
}

void AKnight::SetICanShootAgain()
{
	bCanIShoot = true;
}

