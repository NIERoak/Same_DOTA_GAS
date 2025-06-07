#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"



UENUM(BlueprintType)
enum class ETeamID :uint8
{
	None     UMETA(DisplayName = "None"),
	Team1     UMETA(DisplayName = "Team 1"),
	Team2     UMETA(DisplayName = "Team 2"),
	Team3     UMETA(DisplayName = "Team 3"),
	Team4     UMETA(DisplayName = "Team 4"),
	Team5     UMETA(DisplayName = "Team 5"),
	Team6     UMETA(DisplayName = "Team 6"),
	Team7     UMETA(DisplayName = "Team 7"),
	Team8     UMETA(DisplayName = "Team 8"),
	Team9     UMETA(DisplayName = "Team 9"),
	Team10     UMETA(DisplayName = "Team 10"),
	Team11     UMETA(DisplayName = "Team 11"),
	Team12     UMETA(DisplayName = "Team 12"),
};

UENUM(BlueprintType)
enum class EPlayerID :uint8
{
	None        UMETA(DisplayName = "None"),
	Player1     UMETA(DisplayName = "Player 1"),
	Player2     UMETA(DisplayName = "Player 2"),
	Player3     UMETA(DisplayName = "Player 3"),
	Player4     UMETA(DisplayName = "Player 4"),
	Player5     UMETA(DisplayName = "Player 5"),
	Player6     UMETA(DisplayName = "Player 6"),
	Player7     UMETA(DisplayName = "Player 7"),
	Player8     UMETA(DisplayName = "Player 8"),
	Player9     UMETA(DisplayName = "Player 9"),
	Player10     UMETA(DisplayName = "Player 10"),
	Player11     UMETA(DisplayName = "Player 11"),
	Player12     UMETA(DisplayName = "Player 12"),
};