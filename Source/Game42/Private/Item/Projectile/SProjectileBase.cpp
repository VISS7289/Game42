// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Projectile/SProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Game/SGameplayFunctionLibrary.h"

// Sets default values
ASProjectileBase::ASProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DestoryPrjDelay = 10.0f; // ������10s
	Damage = 20.0f; // Ĭ���˺�20

	// ����������
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;
	// ���Ͷ�����ƶ����
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.0f;
}

void ASProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentHit.AddDynamic(this, &ASProjectileBase::OnActorHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASProjectileBase::OnActorOverlap);
}

// Called when the game starts or when spawned
void ASProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	// ���Է�����
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	// �����������ټ�ʱ��
	GetWorldTimerManager().SetTimer(FTimerHandle_DestoryPrjDelay, this, &ASProjectileBase::DestoryPrj, DestoryPrjDelay);
}

void ASProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void ASProjectileBase::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		USGameplayFunctionLibrary::ApplyDamage(GetInstigator(), OtherActor, Damage);
		Explode();
	}
}

void ASProjectileBase::Explode_Implementation()
{
	if (ensure(!IsPendingKill()))
	{
		// ��ײ����ʧ
		DestoryPrj();
	}
}

// ��������
void ASProjectileBase::DestoryPrj()
{
	// ���������ʱ��
	GetWorldTimerManager().ClearTimer(FTimerHandle_DestoryPrjDelay);
	Destroy();
}



// Called every frame
void ASProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

