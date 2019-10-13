// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class RUINSESCAPE2_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
/*
  Generamos una variable de velocidad para que las plataformas puedan tener diferentes
  Velocidades dependiendo lo que indiquemos en el editor.
*/
	UPROPERTY(EditAnywhere)
	float MovingSpeed = 20;

//Dejamos visible el widget para acomodar la posicion hasta la cual llega la plataforma y vuelve a su punto original
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

//Es el encargado de contabilizar los trigger activados cuando se pulsa el trigger para mover o no la plataforma
	void AddActiveTrigger();
//Es el encargado de restar la cantidad de triggers cuando se deja de pulsar el trigger para dejar de mover la plataforma
	void RemoveActiveTrigger();
private:

	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;

//Por defecto dejamos uno ya que siendo mayor a cero la plataforma se mueve sola, si es cero espera que haya un trigger para activarla
	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;
};