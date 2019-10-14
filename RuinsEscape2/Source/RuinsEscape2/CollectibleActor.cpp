// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleActor.h"

//Agregamos nuevos headers
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACollectibleActor::ACollectibleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Seteamos valores por defecto

	//Radio de la sphera default 100.0f
	SphereRadius = 100.0f;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	CollisionSphere->InitSphereRadius(SphereRadius);
	CollisionSphere->SetCollisionProfileName("Trigger");
	RootComponent = CollisionSphere;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh Component"));
	StaticMesh->SetupAttachment(RootComponent);

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACollectibleActor::OnOverlapBegin);

	//Valores para manejo de rotacion del objeto
	PitchValue = 0.f;
	YawValue = 0.f;
	RollValue = 0.f;
}

// Called when the game starts or when spawned
void ACollectibleActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACollectibleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//En cada frame se cambia la rotacion del objeto
	FRotator NewRotator = FRotator(PitchValue, YawValue, RollValue);
	FQuat QuatRotation = FQuat(NewRotator);

	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void ACollectibleActor::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//Se hace el contorl de los valores nullos y si el otro actor que comienza el overpal tiene el tag de "Player" el objeto se destruye
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor->ActorHasTag("Player")))
	{
		Destroy();
	}
}

