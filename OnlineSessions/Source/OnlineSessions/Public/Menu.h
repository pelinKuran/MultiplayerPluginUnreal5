// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class ONLINESESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void MenuSetup(int32 NumOfPublicCOnnections = 4, FString TypeOfMatch = FString(TEXT("FreeForAll")), FString PathToLobby = FString(TEXT("/Game/Lobby")));
protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;
	//Callbacks for the custom delegates created on MultiplayerSessionSubSystem
	UFUNCTION()
	void OnCreateSession(bool bWasSusccessful);
	UFUNCTION()
	void OnDestroySession(bool bWasSusccessful);
	UFUNCTION()
	void OnStartSession(bool bWasSusccessful);
	void OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionSearchResultList, bool bWasSusccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	UPROPERTY(meta = (BindWidget))
		UButton* JoinButton;
	UFUNCTION()
	void HostButtonClicked();
	UFUNCTION()
	void JoinButtonClicked();
	void MenuTearDown();
	//Subsytem designed to handle online session functionality
	class UMultiplayerSessionsSubsystem* MultiplayerSessionSubsytem;
	int32 NumPublicConnections{ 4 };
	FString typeMatch;
	FString pathToLobby{TEXT("")};
};
