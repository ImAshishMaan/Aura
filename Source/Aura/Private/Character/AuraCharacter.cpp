#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter() {

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	
}


void AAuraCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);

	// Init Ability actor info for the Server
	InitAbilityActorInfo();
	
}

void AAuraCharacter::OnRep_PlayerState() {
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
	
}

void AAuraCharacter::InitAbilityActorInfo() {
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent(); // Replacing the ASC from player state to Character class
	AttributeSet = AuraPlayerState->GetAttributeSet(); // Replacing the AS from player state to Character class

	if(AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController())) {
		if(AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD())) {
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
			
		}
	}
}
