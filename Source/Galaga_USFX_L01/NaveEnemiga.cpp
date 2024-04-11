// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEnemiga.h"

// Sets default values
ANaveEnemiga::ANaveEnemiga()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	// Create the mesh component
	mallaNaveEnemiga = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	//mallaNaveEnemiga->SetStaticMesh(ShipMesh.Object);
	mallaNaveEnemiga->SetupAttachment(RootComponent);
	RootComponent = mallaNaveEnemiga;
	velocidad = 1;
}

// Called when the game starts or when spawned
void ANaveEnemiga::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANaveEnemiga::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ubicacionActual.X > LimiteSuperior) {
		SetActorLocation(FVector(0.0f, ubicacionActual.Y, ubicacionActual.Z));


	}
	if (ubicacionActual.X < Limiteinferior) {
		SetActorLocation(FVector(1530.0f, ubicacionActual.Y, ubicacionActual.Z));
	}

	if (ubicacionActual.Y > LimiteDerecho) {
		SetActorLocation(FVector(ubicacionActual.X, 0.0f, ubicacionActual.Z));
	}
	if (ubicacionActual.Y < LimiteIzquierdo) {
		SetActorLocation(FVector(ubicacionActual.X, 100.0f, ubicacionActual.Z));
	}

}

