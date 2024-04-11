// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveEnemiga.h"
#include "NaveEnemigaEspia.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_USFX_L01_API ANaveEnemigaEspia : public ANaveEnemiga
{
	GENERATED_BODY()

public:

		ANaveEnemigaEspia();
		 
protected:
		
	virtual void Mover(float DeltaTime);
	virtual void Tick(float DeltaTime) override;
	
};
