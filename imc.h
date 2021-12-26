// imc.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <iostream>
#include <string>
#include <random>
#include <unordered_map>


typedef enum {
	PLAYER_WIN,
	TIE,
	COMPUTER_WIN,
} Match_Result;


class User {
public:
	// deleted the copy costractor, because there should be only one user.
	User(const User&) = delete;

	static User& Get() {
		static User instance;
		return instance;
	}

	bool IsPlaying() {
		return m_IsPlaying;
	}

	bool SetPlaying(bool status) {
		return m_IsPlaying = status;
	}

	std::string GetUserInput() {
		std::cout << "Enter 1 to play Rock, 2 to play Paper, and 3 to play Scissors!: ";
		getline(std::cin, Get().m_SUserMove);

		// Convert the user move from a string to an integer
		m_userMove = std::stoi(m_SUserMove);
		
		return m_SUserMove;
	}

	std::string GetUserMove() {
		return m_SUserMove;
	}

	void PlayAgainCheck() {
		std::string playAgain;
		std::cout << "Play again? [y/n]: ";
		getline(std::cin, playAgain);

		if (!(playAgain == "y" || playAgain == "n"))
		{
			std::cout << "Unknown command! Please try again" << std::endl;
			std::cout << "Play again? [y/n]: ";
		}

		if (playAgain == "n")
			m_IsPlaying = false;
	}

private:
	std::string m_SUserMove;
	bool m_IsPlaying;
	int m_userMove;

	User() : m_IsPlaying{ false } {}
};

class GameTable {
public: 
	// deleted the copy costractor, because GameTable is Singleton
	GameTable(const GameTable&) = delete; 

	static GameTable& Get() {
		static GameTable instance;
		return instance;
	}

	void OverallResults() {
		return IOverallResults();
	}

	void GameLobby() {
		return IGameLobby();
	}

	void StartNewGame() {
		User::Get().SetPlaying(true);
	}

	void GetRandomInt() {
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_int_distribution<> distr(1, 3); // define the range
		// Create random integer in range [1,3] to simulate the computer selecting a move
		Get().compMove = distr(eng);
	}

	void TurnResults() {
		GameTable::Get().GetRandomInt();

		result = userMove - compMove;

		if (result == 0)
			std::cout << "Tie game!" << std::endl;
		else if (result == 1 || result == -2)
		{
			std::cout << "Congratulations, you won!" << std::endl;
			playerWins++;
		}
		else
		{
			std::cout << "Sorry, you lost!" << std::endl;
			compWins++;
		}
	}

private:
	std::unordered_map<int, std::string> moves;
	int playerWins, compWins, compMove, userMove, result;

	GameTable() : moves{ {1, "Rock"}, {2, "Paper"}, {3, "Scissors"} },
		playerWins{ 0 }, compWins { 0 }, compMove{ 0 }, userMove{ 0 }, result{ 0 } {}

	void IOverallResults() {
		std::cout << "Your move: " << moves[userMove] << " // Computer's move: " << moves[compMove] << std::endl;
		std::cout << "Player: " << playerWins << " | Computer: " << compWins << std::endl;
	}

	void IGameLobby() {
		std::cout << "--- Welcome to the Paper-Rock-Scissors Game ---\n";
		std::cout << "--- Press any key to start a new game ---";
		std::cin.get();
		StartNewGame();
	}
};