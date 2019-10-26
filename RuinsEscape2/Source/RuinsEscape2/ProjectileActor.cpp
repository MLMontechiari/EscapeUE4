// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AProjectileActor::AProjectileActor()
{
	//Usamos la sphere para representar las colisiones.
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectileActor::OnHit);

	//Los jugadores no pueden caminar sobre el
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	//Setea como raiz
	RootComponent = CollisionComp;

	//Usamos un StaticMesh para asignar algun objeto X a este projectil
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh Component"));
	StaticMesh->SetupAttachment(RootComponent);

	//Se usa el ProjectileMovement para el movimiento
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	//Se muere luego de 3 segundos si es que no hitea algo y se autodestruye en el HIT
	InitialLifeSpan = 3.0f;
}

void AProjectileActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Solo displaya o se autodestruye cuando hitea al jugador
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && (OtherActor->ActorHasTag("Player")))
	{
		//Cuando toca al jugador displaya aviso en pantalla "HIT al Jugador!!"
		UE_LOG(LogTemp, Warning, TEXT("HIT al Jugador!!"));

		Destroy();
	}
}