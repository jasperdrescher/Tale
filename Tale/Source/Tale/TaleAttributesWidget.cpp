// Fill out your copyright notice in the Description page of Project Settings.


#include "TaleAttributesWidget.h"
#include "TaleAttributeSet.h"
#include "TalePlayerCharacter.h"

void UTaleAttributesWidget::BindToAttributes()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	ATalePlayerCharacter* TalePlayerCharacter = Cast<ATalePlayerCharacter>(PlayerController->GetCharacter());
	TalePlayerCharacter->GetAbilitySystemComponent();

	UAbilitySystemComponent* AbilitySystemComponent = TalePlayerCharacter->GetAbilitySystemComponent();
	const UTaleAttributeSet* FabAS = TalePlayerCharacter->GetAttributeSet();

	// Initial Attributes
	HealthPercent = NUMERIC_VALUE(FabAS, Health) / NUMERIC_VALUE(FabAS, MaxHealth);
	StaminaPercent = NUMERIC_VALUE(FabAS, Stamina) / NUMERIC_VALUE(FabAS, MaxStamina);

	// Attribute Changes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FabAS->GetHealthAttribute()).AddLambda(
		[this, FabAS](const FOnAttributeChangeData& Data)
		{
			HealthPercent = Data.NewValue / NUMERIC_VALUE(FabAS, MaxHealth);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FabAS->GetStaminaAttribute()).AddLambda(
		[this, FabAS](const FOnAttributeChangeData& Data)
		{
			StaminaPercent = Data.NewValue / NUMERIC_VALUE(FabAS, MaxStamina);;
		});
}
