// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyUserWidget.h"
#include "Identity_5/Lobby/Contents/LobbyPlayerState.h"
//#include "Lobby/Contents/LobbyPlayerState.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
//#include "SessionListWidget.h"
#include "Identity_5/SessionListWidget.h"

#include "GameFramework/PlayerState.h"
#include "GameFramework/PlayerController.h"


void ULobbyUserWidget::SetInfo(ALobbyPlayerState* InPlayerState)
{
	PlayerState = InPlayerState;
	RefreshUI();
}

void ULobbyUserWidget::RefreshUI()
{
	if (PlayerState == nullptr)
		return;

	bool isLocalPlayer = false;

	APlayerController* PlayerController = PlayerState->GetPlayerController();
	if (PlayerController)
		isLocalPlayer = PlayerController->IsLocalController();

	bool isReady = PlayerState->Ready;
	bool isServer = UKismetSystemLibrary::IsServer(this);

	Btn_Ready->SetVisibility(ESlateVisibility::Hidden);
	Txt_Ready->SetVisibility(ESlateVisibility::Hidden);
	Editable_PlayerName->SetVisibility(ESlateVisibility::Hidden);

	if (isReady)
		Txt_Ready->SetVisibility(ESlateVisibility::Visible);

	if (isLocalPlayer && isReady == false)
		Btn_Ready->SetVisibility(ESlateVisibility::Visible);

	Editable_PlayerName->SetText(PlayerState->Nickname);
	Editable_PlayerName->SetVisibility(ESlateVisibility::Visible);
	if (isReady)
		Editable_PlayerName->SetIsReadOnly(true);
	else
		Editable_PlayerName->SetIsReadOnly(!isLocalPlayer);
}