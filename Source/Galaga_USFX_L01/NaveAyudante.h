// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Galaga_USFX_L01Pawn.h"
#include "NaveAyudante.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_USFX_L01_API ANaveAyudante : public AGalaga_USFX_L01Pawn
{
	GENERATED_BODY()
	
public:

	ANaveAyudante();

	void SetNaveJugador(class AGalaga_USFX_L01Pawn* NuevaNaveAyudante);

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MueveNaveAyudante(float DeltaSeconds);
	void FireShotAyudante();
	void SetFiringState(bool bNewFiringState);

private:

	class UStaticMeshComponent* ShipMeshComponent;

	class AGalaga_USFX_L01Pawn* NaveJugadorAyudante;

	FTimerHandle TimerHandle_FireRate;

	float FireRate;

	FVector GunOffset;

	uint32 bCanFire;

};
