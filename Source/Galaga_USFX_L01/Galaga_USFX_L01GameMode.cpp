// Copyright Epic Games, Inc. All Rights Reserved.

#include "Galaga_USFX_L01GameMode.h"
#include "Galaga_USFX_L01Pawn.h"
#include "NaveEnemiga.h"
#include "NaveEnemigaTransporte.h"
#include "NaveEnemigaCaza.h"
#include "NaveEnemigaEspia.h"
#include "NaveEnemigaReabastecimiento.h"
#include "NaveEnemigaNodriza.h"

#include "InventoryActor.h"
#include "InventoryComponent.h"
#include "CapsulaEnergia.h"
#include "CapsulaProjectileSlow.h"

AGalaga_USFX_L01GameMode::AGalaga_USFX_L01GameMode()
{
	// set default pawn class to our character class
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = AGalaga_USFX_L01Pawn::StaticClass();

	//NaveEnemiga01 = nullptr;
}

void AGalaga_USFX_L01GameMode::BeginPlay()
{
	Super::BeginPlay();
	//Set the game state to playing

	FVector ColocacionInicialNaves = FVector(-500.0f, 50.0f, 270.f);
	FVector ubicacionInicioNavesEnemigasCaza = FVector(-500.0f, 500.0f, 250.0f);
	FVector ubicacionInicioNavesEnemigasTransporte = FVector(500.0f, 500.0f, 250.0f);

	FVector UbicacionDrop = FVector(200, -300, 215);
	FVector UbicacionEnergia = FVector(300, -300, 215);
	FVector UbicacionCapsulaProjectileSlow = FVector(400, -300, 215);

	InventoryActor = GetWorld()->SpawnActor<AInventoryActor>(UbicacionDrop, FRotator::ZeroRotator);
	CapsulaEnergia = GetWorld()->SpawnActor<ACapsulaEnergia>(UbicacionEnergia, FRotator::ZeroRotator);
	CapsulaProjectileSlow = GetWorld()->SpawnActor<ACapsulaProjectileSlow>(UbicacionCapsulaProjectileSlow, FRotator::ZeroRotator);

	//FVector ubicacionNave01 = FVector(-1000.0f, 500.0f, 250.0f);
	//FVector ubicacionNave02 = FVector(-500.0f, -500.0f, 250.0f);

	FRotator rotacionNave = FRotator(0.0f, 0.0f, 0.0f);

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		FVector ColocacionActual = ColocacionInicialNaves;

		for (int i = 0; i < 5; i++) {

			ColocacionActual = FVector(ColocacionActual.X + 250, ColocacionActual.Y + i, ColocacionActual.Z);
			ANaveEnemigaCaza* NaveEnemigaCazaActual = World->SpawnActor<ANaveEnemigaCaza>(ColocacionActual, rotacionNave);
			TANavesEnemigas.Add(NaveEnemigaCazaActual);

			FString nombre04 = NaveEnemigaCazaActual->GetNombre();

			FString nombreNave04 = FString::Printf(TEXT("%s %d"), *nombre04, i);
			//Mensaje en pantalla
			if (GEngine)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, nombreNave04);
			}

			TMapCambiarVelocidad.Add(nombreNave04, NaveEnemigaCazaActual);
			TMapCambiarVelocidad[nombreNave04]->GetVelocidad();
			TMapCambiarVelocidad[nombreNave04]->SetVelocidad(0.1);
		}

		for (int i = 0; i < 5; i++) {
			ColocacionActual = FVector(ColocacionActual.X - 10, ColocacionActual.Y + 250, ColocacionActual.Z + 4);
			ANaveEnemigaTransporte* NaveEnemigaTransporteMuniciones = World->SpawnActor<ANaveEnemigaTransporte>(ColocacionActual, rotacionNave);
			TANavesEnemigas.Add(NaveEnemigaTransporteMuniciones);

			FString nombre = NaveEnemigaTransporteMuniciones->GetNombre();
			FString nombreNave = FString::Printf(TEXT("%s %d"), *nombre, i);
			//Mensaje en pantalla
			if (GEngine)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, nombreNave);
			}

			TMapCambiarVelocidad.Add(nombreNave, NaveEnemigaTransporteMuniciones);
			TMapCambiarVelocidad[nombreNave]->GetVelocidad();
			TMapCambiarVelocidad[nombreNave]->SetVelocidad(0.1);//accedemos a la velocidad de la nave y la cambiamos; de este modo
		}

		for (int i = 0; i < 5; i++) {
			ColocacionActual = FVector(ColocacionActual.X - 60, ColocacionActual.Y - 270, ColocacionActual.Z);
			ANaveEnemigaEspia* NaveEnemigaEspiaCamuflaje = World->SpawnActor<ANaveEnemigaEspia>(ColocacionActual, rotacionNave);
			TANavesEnemigas.Add(NaveEnemigaEspiaCamuflaje);

			FString nombre02 = NaveEnemigaEspiaCamuflaje->GetNombre();
			FString nombreNave02 = FString::Printf(TEXT("%s %d"), *nombre02, i);
			//Mensaje en pantalla
			if (GEngine)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, nombreNave02);
			}

			TMapCambiarVelocidad.Add(nombreNave02, NaveEnemigaEspiaCamuflaje);
			TMapCambiarVelocidad[nombreNave02]->GetVelocidad();
			TMapCambiarVelocidad[nombreNave02]->SetVelocidad(1);
		}

		for (int i = 0; i < 5; i++) {
			ColocacionActual = FVector(ColocacionActual.X, ColocacionActual.Y - 150, ColocacionActual.Z);
			ANaveEnemigaNodriza* NaveEnemigaNodriza01 = World->SpawnActor<ANaveEnemigaNodriza>(ColocacionActual, rotacionNave);
			TANavesEnemigas.Add(NaveEnemigaNodriza01);

			FString nombre05 = NaveEnemigaNodriza01->GetNombre();
			FString nombreNave05 = FString::Printf(TEXT("%s %d"), *nombre05, i);
			//Mensaje en pantalla
			if (GEngine)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, nombreNave05);
			}

			TMapCambiarVelocidad.Add(nombreNave05, NaveEnemigaNodriza01);
			TMapCambiarVelocidad[nombreNave05]->GetVelocidad();
			TMapCambiarVelocidad[nombreNave05]->SetVelocidad(49);
		}

		//for (int i = 0; i < 7; i++) {
		//	ColocacionActual = FVector(ColocacionActual.X + i + 100, ColocacionActual.Y + 300, ColocacionActual.Z + 3);
		//	ANaveEnemigaCazaPesado* NaveEnemigaCazaPesadoActual = World->SpawnActor<ANaveEnemigaCazaPesado>(ColocacionActual, rotacionNave);
		//	TANavesEnemigas.Add(NaveEnemigaCazaPesadoActual);


		//	FString nombre06 = NaveEnemigaCazaPesadoActual->GetNombre();
		//	FString nombreNave06 = FString::Printf(TEXT("%s %d"), *nombre06, i);
		//	//Mensaje en pantalla
		//	if (GEngine)
		//	{
		//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, nombreNave06);
		//	}

		//	TMapCambiarVelocidad.Add(nombreNave06, NaveEnemigaCazaPesadoActual);
		//	TMapCambiarVelocidad[nombreNave06]->GetVelocidad();
		//	TMapCambiarVelocidad[nombreNave06]->SetVelocidad(49);
		//}























		//for (int i = 0; i < 5; i++) {
		//	FVector PosicionNaveActual = FVector(ubicacionInicioNavesEnemigasCaza.X, ubicacionInicioNavesEnemigasCaza.Y + i * 300, ubicacionInicioNavesEnemigasTransporte.Z);
		//	ANaveEnemigaCaza* NaveEnemigaCazaTemporal = World->SpawnActor<ANaveEnemigaCaza>(PosicionNaveActual, rotacionNave);

		//	//TANavesEnemigasCaza.Push(NaveEnemigaCazaTemporal);
		//	TANavesEnemigas.Push(NaveEnemigaCazaTemporal);
		//}

		//float nuevaposicionX = ubicacionInicioNavesEnemigasTransporte.X - 300.0f;

		//for (int j = 0; j < 5; j++) {
		//	FVector PosicionNaveActual = FVector(nuevaposicionX, ubicacionInicioNavesEnemigasTransporte.Y + j * 300, ubicacionInicioNavesEnemigasTransporte.Z);
		//	ANaveEnemigaTransporte* NaveEnemigaTransporteTemporal = World->SpawnActor<ANaveEnemigaTransporte>(PosicionNaveActual, rotacionNave);

		//	//TANavesEnemigasTransporte.Push(NaveEnemigaTransporteTemporal);
		//	TANavesEnemigas.Push(NaveEnemigaTransporteTemporal);
		//}

		////NaveEnemigaTransporte01 = World->SpawnActor<ANaveEnemigaTransporte>(ubicacionNave01, rotacionNave);
		////NaveEnemigaCaza01 = World->SpawnActor<ANaveEnemigaCaza>(ubicacionNave02, rotacionNave);

		//TiempoTranscurrido = 0;
	}

	/*NaveEnemigaCaza01->SetPosicion(FVector(-500.0f, 500.0f, 200.0f));
	NaveEnemigaTransporte01->SetPosicion(FVector(500.0f, -500.0f, 200.0f));*/

}

void AGalaga_USFX_L01GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*TiempoTranscurrido++;

	if (TiempoTranscurrido >= 100)
	{
		int numeroEnemigo = FMath::RandRange(0, 9);
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Hola estoy aqui")));


			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Entero: %d"), numeroEnemigo));
			
		}
		TANavesEnemigas[numeroEnemigo]->PrimaryActorTick.bCanEverTick = false;
		TANavesEnemigas[numeroEnemigo]->SetVelocidad(0);
	}*/
}
