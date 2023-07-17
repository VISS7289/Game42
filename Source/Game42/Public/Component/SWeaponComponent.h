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

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	USWeaponComponent* GetWeaponComp(AActor* FromActor);

protected:

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UStaticMeshComponent* WeaponMesh; // ǹе������

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<ASProjectileBase> DefaultBullet; // Ĭ���ӵ�

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	int32 BulletNumMax; // �ӵ�����

	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	TArray<TSubclassOf<ASProjectileBase>> BulletInGun; // ǹе���ִ��ӵ�

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	TSubclassOf<ASProjectileBase> Fire(); // ����

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AddBullet(TSubclassOf<ASProjectileBase> ProjectileClass); // װ��

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AddAll(); // װ��

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
