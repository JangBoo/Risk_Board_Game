#pragma once
#include "Cards.h"
#include "Dice.h"
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include "PlayerStrategies.h"

using namespace std;

//Forward declaration
class GameBoard;
class GameLoop;

class GameEngine {
private:
public:
	//static GameBoard* gameboard;
	static GameBoard* gameboard;
	//Constructor - old
	GameEngine(GameBoard& gm);
	~GameEngine();

	//Ask the user for the map he wants to play
	static Map mapSelector();
	
	//Ask the user for the number of player and their names
	static vector<Player> numberOfPlayer();

	//Make a gameboard object containing a map, list of player and a deck of card
	static GameBoard initiateGame();

	// Orders the players randomly
	void orderPlayers();

	// Assigns Countries to each Player
	void assignCountries();

	// Assigns armies to whichever country the player chooses
	void placeArmies();

	// GameLoop
	void runLoop();
};

class GameBoard {
private:
	Map* _map;
	Deck* _deckOfCards;
	vector<Player>* _listPlayer;

public:

	GameBoard();
	GameBoard(Map& map, Deck& deck, vector<Player>& players);
	GameBoard(const GameBoard& gm);

	void operator=(const GameBoard& gm);

	//Getters
	Map getMap() const;
	vector<Player> getListPlayer() const;
	Deck getDeckOfCard() const;

	//Getter - pointer
	vector<Player>* getListPlayerPtr() const;
	Map* getMapPtr() const;
	Deck* getDeckOfCardPtr() const;
	
	//Setters
	void setListPlayer(vector<Player>& listPlayer);

};

class GameLoop {
private:
	vector<Player>* listPlayer;
	vector<Country>* _listCountry;
public:
	GameLoop();
	GameLoop(vector<Player>& listPlayer, vector<Country>& listCountry);
	GameLoop(const GameLoop& gameloop);
	~GameLoop();

	//Getters
	vector<Player> getlistPlayer() const;
	vector<Country> getlistCountry() const;


	static void executeLoop(vector<Player*>& players, vector<Country>& Countrys); // maybe it's better to put continent and get the whole list. check it later.

};