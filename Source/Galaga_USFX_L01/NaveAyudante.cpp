// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAyudante.h"
#include "Galaga_USFX_L01Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Galaga_USFX_L01Projectile.h"

ANaveAyudante::ANaveAyudante()
{
	PrimaryActorTick.bCanEverTick = true;

	FireRate = 0.1f;
	GunOffset = FVector(90.f, 0.f, 0.f);

	bCanFire = true;
}

void ANaveAyudante::SetNaveJugador(AGalaga_USFX_L01Pawn* NuevaNaveAyudante)
{
	NaveJugadorAyudante = NuevaNaveAyudante;
}

void ANaveAyudante::BeginPlay()
{
	Super::BeginPlay();

	
}

void ANaveAyudante::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (NaveJugadorAyudante)
	{
		MueveNaveAyudante(DeltaTime);
		//if (NaveJugadorAyudante->bCanFire)
		//{
			/*if (NaveJugadorAyudante->bCanFire && !GetWorldTimerManager().IsTimerActive(TimerHandle_FireRate))
			{
				bCanFire = true;
				FireShotAyudante();
			}*/
		if (NaveJugadorAyudante && NaveJugadorAyudante->bCanFire)
		{
			FireShotAyudante();
		}
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No se ha asignado una nave jugador a la nave ayudante"));
	}
}

void ANaveAyudante::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANaveAyudante::MueveNaveAyudante(float DeltaSeconds)
{
	if (NaveJugadorAyudante)
	{
		FVector NuevaPosicion = NaveJugadorAyudante->GetActorLocation();
		NuevaPosicion.Y += 150.f;
		SetActorLocation(NuevaPosicion);
	}
}

void ANaveAyudante::FireShotAyudante()
{
    if (NaveJugadorAyudante)
    {
        // Calculate fire direction based on player pawn's rotation
        const FRotator FireRotation = NaveJugadorAyudante->GetActorRotation();
        const FVector FireDirection = FireRotation.Vector();

        // If we are pressing fire stick in a direction
        if (FireDirection.SizeSquared() > 0.0f)
        {
            // Spawn projectile at an offset from this pawn
            const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

            UWorld* const World = GetWorld();
            if (World != nullptr)
            {
				if (bCanFire)
				{
					// Spawn the projectile
					World->SpawnActor<AGalaga_USFX_L01Projectile>(SpawnLocation, FireRotation);

					// Set timer to enable firing again after FireRate seconds
					World->GetTimerManager().SetTimer(TimerHandle_FireRate, [&]()
						{
							SetFiringState(true);
						}, FireRate, false);
					SetFiringState(false);
				}
            }
        }
    }
}

void ANaveAyudante::SetFiringState(bool bNewFiringState)
{
	bCanFire = bNewFiringState;
}
