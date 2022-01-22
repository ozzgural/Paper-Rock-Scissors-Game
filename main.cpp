// main.cpp : Defines the entry point for the application.
//

#include "main.h"

int main()
{
    auto& user = User::Get();
    auto& game_table = GameTable::Get();

    game_table.GameLobby();

    while (user.IsPlaying())
    {
        user.GetUserInput();

        game_table.TurnResults();
        game_table.OverallResults();

        user.PlayAgainCheck();
    }

    return 0;
}
