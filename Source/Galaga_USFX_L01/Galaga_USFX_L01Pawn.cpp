// Copyright Epic Games, Inc. All Rights Reserved.

#include "Galaga_USFX_L01Pawn.h"
#include "Galaga_USFX_L01Projectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Bomba.h"
#include "NaveAyudante.h"

const FName AGalaga_USFX_L01Pawn::MoveForwardBinding("MoveForward");
const FName AGalaga_USFX_L01Pawn::MoveRightBinding("MoveRight");
const FName AGalaga_USFX_L01Pawn::FireForwardBinding("FireForward");
const FName AGalaga_USFX_L01Pawn::FireRightBinding("FireRight");


AGalaga_USFX_L01Pawn::AGalaga_USFX_L01Pawn()
{	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);

	// Initialize the bomb class
	BombaClass = ABomba::StaticClass();
	
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	// Movement
	MoveSpeed = 1000.0f;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;

	MyInventory = CreateDefaultSubobject<UInventoryComponent>("MyInventory");

	Jumping = false;
	DuracionSalto = 1.0f;
	
}

void AGalaga_USFX_L01Pawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(FireRightBinding);

	PlayerInputComponent->BindAction("DropItem", EInputEvent::IE_Pressed, this, &AGalaga_USFX_L01Pawn::DropItem);
	PlayerInputComponent->BindAction("Teletransportacion", EInputEvent::IE_Pressed, this, &AGalaga_USFX_L01Pawn::Teletransportacion);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AGalaga_USFX_L01Pawn::Jump);
	PlayerInputComponent->BindAction("LanzarBomba", IE_Pressed, this, &AGalaga_USFX_L01Pawn::LanzarBomba);

	PlayerInputComponent->BindAction("SpawnNaveAyudante", IE_Pressed, this, &AGalaga_USFX_L01Pawn::SpawnNaveAyudante);
}

void AGalaga_USFX_L01Pawn::Tick(float DeltaSeconds)
{
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}
	
	// Create fire direction vector
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);

	// Try and fire a shot
	FireShot(FireDirection);
	if (NaveAyudanteInstance)
	{
		NaveAyudanteInstance->SetFiringState(bCanFire);
	}
}

void AGalaga_USFX_L01Pawn::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bCanFire == true)
	{
		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				// spawn the projectile
				World->SpawnActor<AGalaga_USFX_L01Projectile>(SpawnLocation, FireRotation);
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AGalaga_USFX_L01Pawn::ShotTimerExpired, FireRate);

			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanFire = false;
			//SetFiringState(true);
		}
	}
}

void AGalaga_USFX_L01Pawn::ShotTimerExpired()
{
	bCanFire = true;
}

void AGalaga_USFX_L01Pawn::DropItem()
{
	if (MyInventory->CurrentInventory.Num() == 0)
	{
		return;
	}
	AInventoryActor* Item =
		MyInventory->CurrentInventory.Last();
	MyInventory->RemoveFromInventory(Item);

	FVector ItemOrigin;
	FVector ItemBounds;
	Item->GetActorBounds(false, ItemOrigin, ItemBounds);
	FTransform PutDownLocation = GetTransform() + FTransform(RootComponent->GetForwardVector() * ItemBounds.GetMax());
	Item->PutDown(PutDownLocation);

}

void AGalaga_USFX_L01Pawn::TakeItem(AInventoryActor* InventoryItem)
{
	InventoryItem->PickUp();
	MyInventory->AddToInventory(InventoryItem);
}

void AGalaga_USFX_L01Pawn::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	AInventoryActor* InventoryItem =
		Cast<AInventoryActor>(Other);
	if (InventoryItem != nullptr)
	{
		TakeItem(InventoryItem);
	}
}

void AGalaga_USFX_L01Pawn::TeleporTo(FVector Destination, FRotator NewRotation)
{
	SetActorLocation(Destination);
}

void AGalaga_USFX_L01Pawn::Jump()
{
	/*if (Jumping == false)
	{
		Jumping = true;
		FVector JumpDirection = FVector(0, 0, 1000);
		RootComponent->MoveComponent(JumpDirection, FRotator(0, 0, 0), true);
	
	}*/

	if (!Jumping)
	{
		Jumping = true;

		// Save current location of the ship before jumping
		FVector Retorno = GetActorLocation();

		// Calculate target location after jump
		FVector JumpDirection = FVector(0, 0, 500); // Adjust jump height as needed
		FVector TargetLocation = Retorno + JumpDirection;

		// Perform the jump by moving the root component to the target location
		RootComponent->SetWorldLocation(TargetLocation);

		// Call callback function to return to original location after a certain time
		GetWorld()->GetTimerManager().SetTimer(SaltoRetorno, this, &AGalaga_USFX_L01Pawn::RetornarSalto, DuracionSalto, false);
	}
}

void AGalaga_USFX_L01Pawn::RetornarSalto()
{
	// Devuelve la nave a la posición original
	//RootComponent->SetWorldLocation(Retorno);

	// Reinicia la variable de salto
	Jumping = false;

}

void AGalaga_USFX_L01Pawn::LanzarBomba()
{
	if (BombaClass)
	{
		float LaunchAngle = 15.0f; // Ángulo de lanzamiento en el eje Z
		float LaunchSpeed = 500.0f; // Velocidad de lanzamiento

		// Calcular la dirección del lanzamiento basado en la rotación actual de la nave
		FVector LaunchDirection = GetActorForwardVector(); // Obtener el vector de dirección hacia adelante de la nave
		LaunchDirection.Z += FMath::Tan(FMath::DegreesToRadians(LaunchAngle)); // Aplicar la inclinación en el eje Z

		// Normalizar el vector de dirección del lanzamiento
		LaunchDirection.Normalize();

		// Calcular la velocidad de lanzamiento en función de la velocidad y la dirección del lanzamiento
		FVector LaunchVelocity = LaunchDirection * LaunchSpeed;

		FRotator SpawnRotation = GetActorRotation();

		// Spawn the bomb
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		ABomba* Bomba = GetWorld()->SpawnActor<ABomba>(BombaClass, GetActorLocation(), SpawnRotation, SpawnParams);

		// Configurar la velocidad inicial de la bomba
		Bomba->LanzarBomba(LaunchVelocity);

		// Programar la caída de la bomba con un temporizador
		float FallDelay = 2.0f; // Tiempo de retraso antes de que la bomba comience a caer (en segundos)
		FTimerHandle TimerHandle_Fall;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Fall, [this, Bomba]()
			{
				// Iniciar la caída de la bomba en el eje Z con una velocidad hacia abajo
				float FallSpeed = 100.0f; // Velocidad de caída de la bomba
				Bomba->LanzarBomba(FVector(0, 0, -FallSpeed));
			}, FallDelay, false);
	}
}

void AGalaga_USFX_L01Pawn::SpawnNaveAyudante()
{
	// Spawn the helper ship
	if (!NaveAyudanteInstance && GetWorld())
	{
		NaveAyudanteInstance = GetWorld()->SpawnActor<ANaveAyudante>(ANaveAyudante::StaticClass(), FTransform());
		if (NaveAyudanteInstance)
		{
			// Set the player ship as the parent of the helper ship
			NaveAyudanteInstance->SetNaveJugador(this);
		}
	}
}

// Function to handle teleportation input
void AGalaga_USFX_L01Pawn::Teletransportacion()
{
	// Example teleportation des	tination and rotation
	FVector TeleportDestination(1000, 0, 0);
	FRotator TeleportRotation(0, 0, 0);

	// Call the teleport function
	TeleportTo(TeleportDestination, TeleportRotation);
}

//SALTO EN EL EJE Z

//if (!Jumping)
//{
//	Jumping = true;
//
//	// Save current location of the ship before jumping
//	FVector Retorno = GetActorLocation();
//
//	// Calculate target location after jump
//	//FVector JumpDirection = FVector(0, 0, 500); // Adjust jump height as needed
//	//FVector TargetLocation = Retorno + JumpDirection;
//
//	const float MoveDistance = 1000.0f;
//	const FVector  MoveDirection = GetActorForwardVector();
//	const FVector TargetLocation = Retorno + MoveDirection * MoveDistance;
//
//	// Perform the jump by moving the root component to the target location
//	RootComponent->SetWorldLocation(TargetLocation);
//
//	// Call callback function to return to original location after a certain time
//	GetWorld()->GetTimerManager().SetTimer(SaltoRetorno, this, &AGalaga_USFX_L01Pawn::RetornarSalto, DuracionSalto, false);
//}