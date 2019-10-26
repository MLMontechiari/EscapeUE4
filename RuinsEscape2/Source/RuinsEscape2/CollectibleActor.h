// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectibleActor.generated.h"

UCLASS()
class RUINSESCAPE2_API ACollectibleActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACollectibleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Declaracion de los float que van a generar el movimiento de rotacion se cambian desde el editor.
	UPROPERTY(EditAnyWhere, Category = "Movement")
	float PitchValue;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float YawValue;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RollValue;

	//Declaracion del objeto para detectar colisiones
	UPROPERTY(VisibleAnywhere)
	class USphereComponent * CollisionSphere;

	//Declaramos el StaticMesh
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;

	//Declaramos variable para el manejo del radio de la sphere
	UPROPERTY(VisibleAnywhere)
	float SphereRadius;

	//Manejo de cuando comienza el overlap
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
