// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomba.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABomba::ABomba()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create and attach the bomb mesh
    BombaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombaMesh"));
    RootComponent = BombaMesh;

    // Load the bomb mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> BombaMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Trim_90_Out.Shape_Trim_90_Out'"));
    if (BombaMeshAsset.Succeeded())
    {
        BombaMesh->SetStaticMesh(BombaMeshAsset.Object);
    }

    // Initialize the bomb velocity
    BombaVelocity = FVector::ZeroVector;
}


void ABomba::LanzarBomba(const FVector Velocity)
{
    BombaVelocity = Velocity;
}

// Called when the game starts or when spawned
void ABomba::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABomba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    SetActorLocation(GetActorLocation() + BombaVelocity * DeltaTime);
}

