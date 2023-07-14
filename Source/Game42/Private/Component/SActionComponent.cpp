// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SActionComponent.h"
#include "Actions/SAction.h"
#include "Game/SGameplayFunctionLibrary.h"
#include "Engine/ActorChannel.h"

// Sets default values for this component's properties
USActionComponent::USActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// ��ʼ��Ϸʱ��ʼ��Actions
void USActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<USAction> ActionClass : DefaultActions)
	{
		AddAction(GetOwner(), ActionClass);
	}

}


// Debug�鿴Action״̬
void USActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FString DebugMsg = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, DebugMsg);

	//// Debug�鿴Action״̬
	//for (USAction* Action : Actions)
	//{
	//	FColor TextColor = Action->IsRunning() ? FColor::Blue : FColor::White;
	//	FString ActionMsg = FString::Printf(TEXT("[%s] Action: %s ; Outer: %s"),
	//		*GetNameSafe(GetOwner()),
	//		*GetNameSafe(Action),
	//		*GetNameSafe(Action->GetOuter()));

	//	USGameplayFunctionLibrary::LogOnScreen(this, ActionMsg, TextColor, 0.0f);
	//}
}

// ����ж�
// ��������������Ӿ�����ж�
void USActionComponent::AddAction(AActor* InstigatorActor, TSubclassOf<USAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	USAction* NewAction = NewObject<USAction>(GetOwner(), ActionClass);
	if (ensure(NewAction))
	{
		NewAction->Initialize(this);
		Actions.Add(NewAction);
		// �������Ϊ�Զ�����
		if (NewAction->bAutoStart && ensure(NewAction->CanStart(InstigatorActor)))
		{
			NewAction->StartAction(InstigatorActor);
		}
	}

}

// �Ƴ��ж�
// �ж��ж�����ȷ�Ժ�����Ƴ�
void USActionComponent::RemoveAction(USAction* ActionToRemove)
{
	if (ensure(ActionToRemove))
	{
		Actions.Remove(ActionToRemove);
	}
}

// �����ж�
// �������п����ж��������ж�����ִ�ж�Ӧ�ж������Ҹ��ݱ�ǩ�����ж��Ƿ����ִ��
bool USActionComponent::StartActionByName(AActor* InstigatorActor, FName ActionName)
{
	for (USAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->CanStart(InstigatorActor))
			{
				Action->StartAction(InstigatorActor);
				return true;
			}
			else
			{
				FString DebugMsg = FString::Printf(TEXT("Failed To Run: %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, DebugMsg);
			}
		}
	}
	return false;
}

// �����ж�
// �������п����ж��������ж����ƽ�����Ӧ�ж������Ҹ�������״̬�ж��Ƿ����ִ��
bool USActionComponent::StopActionByName(AActor* InstigatorActor, FName ActionName)
{
	for (USAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->IsRunning())
			{
				Action->StopAction(InstigatorActor);
				return true;
			}
			else
			{
				FString DebugMsg = FString::Printf(TEXT("Failed To Stop: %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, DebugMsg);
			}

		}
	}
	return false;
}

USActionComponent* USActionComponent::GetActionComp(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USActionComponent>(FromActor->GetComponentByClass(USActionComponent::StaticClass()));
	}

	return nullptr;
}