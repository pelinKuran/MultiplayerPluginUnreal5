// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Components/Button.h"
#include "MultiplayerSessionsSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

void UMenu::MenuSetup(int32 NumOfPublicCOnnections, FString TypeOfMatch, FString PathToLobby)
{
	pathToLobby = FString::Printf(TEXT("%s?listen"), *PathToLobby);
	NumPublicConnections = NumOfPublicCOnnections;
	typeMatch = TypeOfMatch;
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = 1;
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			//Allow input to be processed only for the UI widget.
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}		
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionSubsytem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();  
	}
	//bind the callback
	if (MultiplayerSessionSubsytem)
	{
		MultiplayerSessionSubsytem->MultiplayerOnSessionCreateComplete.AddDynamic(this, &ThisClass::OnCreateSession);
		MultiplayerSessionSubsytem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
		MultiplayerSessionSubsytem->MultiplayerOnStartSessionComplete.AddDynamic(this, &ThisClass::OnStartSession);
		MultiplayerSessionSubsytem->MultiplayerOnFindSessionComplete.AddUObject(this, &ThisClass::OnFindSession);
		MultiplayerSessionSubsytem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);
	}
}

bool UMenu::Initialize()
{
	if (!Super::Initialize())
		return false;
	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}
	return true;
}

void UMenu::NativeDestruct()
{
	MenuTearDown();
	Super::NativeDestruct();
}

void UMenu::OnCreateSession(bool bWasSuccessful)
{
	if(bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString("Session Created"));
		}
		UWorld* World = GetWorld();
		if (World)
		{
			if (World->ServerTravel(pathToLobby))
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Lobby Valid")));
			else
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Lobby invalid")));

		}
		else 
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString("World not valid "));


	}
	else 
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString("Session Not Created"));
		}
		HostButton->SetIsEnabled(true);
	}

}

void UMenu::OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionSearchResultList, bool bWasSusccessful)
{
	if (MultiplayerSessionSubsytem == nullptr)
		return;
	
	
	for (auto result: SessionSearchResultList)
	{
		FString SettingsValue;
		result.Session.SessionSettings.Get(FName("MatchType"), SettingsValue);
		if (SettingsValue == typeMatch)
		{
			MultiplayerSessionSubsytem->JoinSession(result);
			return;
		}
	}
	if (!bWasSusccessful || SessionSearchResultList.Num() == 0)
	{
		JoinButton->SetIsEnabled(true);

	}
}

void UMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		auto SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			FString address;
			SessionInterface->GetResolvedConnectString(NAME_GameSession, address);
			APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
			if (PlayerController)
			{
				PlayerController->ClientTravel(address, ETravelType::TRAVEL_Absolute);
			}
		}

	}
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		JoinButton->SetIsEnabled(true);
	}

}


void UMenu::OnDestroySession(bool bWasSusccessful)
{
}

void UMenu::OnStartSession(bool bWasSusccessful)
{
}

void UMenu::HostButtonClicked()
{
	HostButton->SetIsEnabled(false);
	if (MultiplayerSessionSubsytem)
	{
		MultiplayerSessionSubsytem->CreateSession(NumPublicConnections, typeMatch);		
	}
}

void UMenu::JoinButtonClicked()
{
	JoinButton->SetIsEnabled(false);
	if (MultiplayerSessionSubsytem)
	{
		MultiplayerSessionSubsytem->FindSessions(10000);
	}
}

void UMenu::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);

		}

	}
}
