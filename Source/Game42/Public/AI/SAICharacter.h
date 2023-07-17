// Fill out your copyright notice in the Description page of Project Settings.
// 该类为一个AI
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class USAttributeComponent; // 属性组件
class UUserWidget; // UI
class USWorldUserWidget; // AI血条UI

UCLASS()
class GAME42_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASAICharacter();

protected:

	USWorldUserWidget* ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UUserWidget> HealthBarWidgetClass; // 敌人血条UI

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		USAttributeComponent* AttributeComp; // 属性组件

	// 注册事件回调函数
	virtual void PostInitializeComponents() override;

	// 生命值改变时
	UFUNCTION()
		void GetHealthChange(AActor* InstigatordActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

};

