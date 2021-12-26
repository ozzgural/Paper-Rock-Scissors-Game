// imc.cpp : Defines the entry point for the application.
//

#include "imc.h"

int main()
{
    auto& user = User::Get();
    auto& game_table = GameTable::Get();

    std::string input = "";
    game_table.GameLobby();


    while (user.IsPlaying())
    {
        input = user.GetUserInput();

        if (!(input == "1" || input == "2" || input == "3"))
        {
            std::cout << "Unknown command: Please try again" << std::endl;
            continue;
        }

        game_table.TurnResults();

        user.PlayAgainCheck();
     
        game_table.OverallResults();
    }

    return 0;
}