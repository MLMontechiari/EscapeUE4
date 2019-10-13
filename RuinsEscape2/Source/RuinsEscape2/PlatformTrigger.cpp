// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"

//Agregamos nuevo header
#include "Components/BoxComponent.h"

//Incluyo el header de la clase de las plataformas q se mueven
#include "MovingPlatform.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creamos UBoxComponent llamado TriggerVolume para manejar los overlap event
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));

	//Para evitar que creashee el editor se realiza la validacion si el TriggerVolume no es null
	if (!ensure(TriggerVolume != nullptr)) return;

	//Creamos el componente Raiz de este ACTOR
	RootComponent = TriggerVolume;

	//Seteamos una notificacion cuando este componente hace overlap con algo
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//Cuando comienza el overlap como prueba enviamos un mensaje por pantalla diciendo "ACTIVADO"
	UE_LOG(LogTemp, Warning, TEXT("Activado!!"));
	
	for (AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->AddActiveTrigger();
	}
}

void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	//Cuando termina el overlap como prueba enviamos un mensaje por pantalla diciendo "DESACTIVADO"
	UE_LOG(LogTemp, Warning, TEXT("Desactivado!!"));

	for (AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->RemoveActiveTrigger();
	}
}

