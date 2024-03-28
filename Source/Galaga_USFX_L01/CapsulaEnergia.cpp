// Fill out your copyright notice in the Description page of Project Settings.


#include "CapsulaEnergia.h"

ACapsulaEnergia::ACapsulaEnergia()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Hex_Tile_Pulse.M_Tech_Hex_Tile_Pulse'"));
	GetStaticMeshComponent()->SetMaterial(0, Material.Object);
}
