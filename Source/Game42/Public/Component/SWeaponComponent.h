// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SWeaponComponent.generated.h"

class UStaticMeshComponent; // ��̬������
class ASProjectileBase; // �ӵ�����

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME42_API USWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USWeaponComponent();

protected:

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* WeaponMesh; // ǹе������

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<ASProjectileBase> DefaultBullet; // Ĭ���ӵ�

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 BulletNumMax; // �ӵ�����

	UPROPERTY(BlueprintReadWrite)
		TArray<TSubclassOf<ASProjectileBase>> BulletInGun; // ǹе���ִ��ӵ�

	UFUNCTION(BlueprintCallable)
		TSubclassOf<ASProjectileBase> Fire(); // ����

	UFUNCTION(BlueprintCallable)
		void AddBullet(TSubclassOf<ASProjectileBase> ProjectileClass); // װ��

	UFUNCTION(BlueprintCallable)
		void AddAll(); // װ��

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
