// main.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <iostream>
#include <string>
#include <random>
#include <unordered_map>


class User {
public:
	// deleted the copy constructor, because there should be only one user.
	User(const User&) = delete;

	static User& Get() {
		static User instance;
		return instance;
	}

	bool IsPlaying() const {
		return m_IsPlaying;
	}

	bool SetPlaying(bool status) {
		return m_IsPlaying = status;
	}

	std::string GetUserInput() {
		std::string input;
		std::cout << "Enter 1 to play Rock, 2 to play Paper, and 3 to play Scissors: ";

		getline(std::cin, input);

		while (!(input == "1" || input == "2" || input == "3"))
		{
			std::cout << "Unknown command: Please try again" << std::endl;
			std::cout << "Enter 1 to play Rock, 2 to play Paper, and 3 to play Scissors: ";
			getline(std::cin, input);
			
		}
		Get().m_SUserMoveStr = input;
		// Convert the user move from a string to an integer
		m_UserMove = std::stoi(m_SUserMoveStr);
		
		return m_SUserMoveStr;
	}

	int GetUserMove() const {
		return m_UserMove;
	}

	void PlayAgainCheck() {
		std::string playAgain;
		std::cout << "Play again? [y/n]: ";
		getline(std::cin, playAgain);

		while (!(playAgain == "y" || playAgain == "n"))
		{
			std::cout << "Unknown command! Please try again" << std::endl;
			std::cout << "Play again? [y/n]: ";
			getline(std::cin, playAgain);
		}

		if (playAgain == "n") {
			m_IsPlaying = false;
		}
	}

private:
	std::string m_SUserMoveStr;
	bool m_IsPlaying;
	int m_UserMove;

	User() :  m_IsPlaying{ false } , m_UserMove{ 0 }{}
};

class GameTable {
public: 
	// deleted the copy constructor, because GameTable is Singleton
	GameTable(const GameTable&) = delete; 

	static GameTable& Get() {
		static GameTable instance;
		return instance;
	}

	void OverallResults() {
		return IOverallResults();
	}

	static void GameLobby() {
		return IGameLobby();
	}

	static void StartNewGame() {
		User::Get().SetPlaying(true);
	}

	static void GetRandomInt() {
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_int_distribution<> uniformIntDistribution(1, 3); // define the range
		// Create random integer in range [1,3] to simulate the computer selecting a move
		Get().compMove = uniformIntDistribution(eng);
	}

	void TurnResults() {
		GetRandomInt();

		int userMove = User::Get().GetUserMove();

		std::cout << "Your move: " << moves[userMove]
			<< " // Computer's move: " << moves[compMove] << std::endl;


		if (userMove == compMove) {
            std::cout << "Tie game" << std::endl;
        }
		else if ((userMove == 1 && compMove == 3) ||
                 (userMove == 2 && compMove == 1) ||
                 (userMove == 3 && compMove == 2))
		{
			std::cout << "Congratulations, you won" << std::endl;
			playerWins++;
		}
		else
		{
			std::cout << "You lost" << std::endl;
			compWins++;
		}
	}

private:
	std::unordered_map<int, std::string> moves;
	int playerWins, compWins, compMove;

	GameTable() : moves{ {1, "Rock"}, {2, "Paper"}, {3, "Scissors"} },
		playerWins{ 0 }, compWins { 0 }, compMove{ 0 } {}

	void IOverallResults() const {

		std::cout << "Player: " << playerWins << " | Computer: " << compWins << std::endl;
	}

	static void IGameLobby() {
		std::cout << "--- Welcome to the Paper-Rock-Scissors Game ---\n";
		StartNewGame();
	}
};
