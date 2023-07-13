// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SHealthWidget.h"
#include "Component/SAttributeComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

USHealthWidget::USHealthWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	HealthChangeCommon(100.0f);
	MaxHealth = Health;
}

// UI�������ʱ������¼�
void USHealthWidget::NativeConstruct()
{

	// ��ȡ���
	APawn* PlayerPawn = GetOwningPlayerPawn();
	if (PlayerPawn)
	{
		// ��ȡ����������
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(PlayerPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (ensureAlways(AttributeComp))
		{
			// ���������������UI����
			HealthChangeCommon(AttributeComp->GetHealth());
			MaxHealth = Health;
			// ������������ OnHealthChanged �� GetHealthChange
			AttributeComp->OnHealthChanged.AddDynamic(this, &USHealthWidget::GetHealthChange);
		}
	}
}

// ����ֵ�ı�ʱ����UI
void USHealthWidget::GetHealthChange(AActor* InstigatordActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	HealthChangeCommon(NewHealth);

	// Ѫ�����ʸ��£��Ѿ����ú��ˣ�ֻ��ҪPrograssAlpha��HealthRate��
	HealthMaterial->SetScalarParameterValue("PrograssAlpha", HealthRate);
}

// ��ͨ��������ֵ����
bool USHealthWidget::HealthChangeCommon(float NewHealth)
{
	Health = NewHealth;
	THealth = FText::FromString(FString::Printf(TEXT("%.2f"), Health));
	HealthRate = Health / MaxHealth;

	return true;
}