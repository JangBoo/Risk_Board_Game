#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Map.h"
#include "Dice.h"
#include "Cards.h"
#include "PlayerStrategies.h"
#include "GameObservers.h"


using namespace std;

class GameBoard;
class GameEngine;
class Hand;
class Dice;

class Player : public PhaseSubject {

private:
	// Attributes
	string* _playerName;
	vector<Country*>* _playerCountries;
	Dice* _playerDice;
	Hand* _playerHand;
	int* _playerArmies;
	int* _numOfExchanges;
	//helper functions
	Strategy* _strategy;
	bool choice(); // Start phase or not.
	void displayCountries(); // Display the countries.
	int chooseOwnCountry(); // Choose country to attack with.
	bool hasEnemyNeighbours(Country& c); // Checks if the player has neighbours to attack.
	vector<Country> getEnemyNeighbours(Country& c); // Get a list of enemy neighbours.

	bool continuePhase(); // Continue the phase or not.
	int chooseSourceCountry(); // Choose source country for fortification.
	bool hasFriendlyNeighbours(Country& c); // Checks if the player has neighbours to fortify.
	int chooseCountryFortify(int size); // Choose a country to fortify.
	vector<Country> getFriendlyNeighbours(Country& c); // Get a list of the friendly neighbours.
	int numOfArmiesToMove(Country& c); // Move a certain number of armies.
	Player* getEnemyPlayer(string enemyName); // Find the corresponding enemy player.
	int getNumOfDice(Country& c, string type); // Get the number of dice rolled.
	vector<int> compareRolls(vector<int> ownRolls, vector<int> defenseRolls); // Compare the rolls pairwise.
	void reinforce2(int* numArmy);
	void placeit(Country* cntry, int* numArmy);
	int continentscores();
	int exchangescore();
	int chooseCountryAttack(int size); // choose which country to attack.

public:
	// Constructors
	Player();
	Player(string name, vector<Country*> countries, Dice  dice, Hand hand, int armies, int numOfExchanges, Strategy* strat);
	Player(const Player& p);

	void operator=(const Player& p);

	// Destructor.
	~Player();

	// Getters.
	string getPlayerName() { return *_playerName; }
	vector<Country*> getPlayerCountries() { return *_playerCountries; }
	vector<Country*>* getPlayerCountriesPtr() { return _playerCountries; }
	Dice getPlayerDice() { return *_playerDice; }
	Hand getPlayerHand() { return *_playerHand; }
	Hand* getPlayerHandPtr() { return _playerHand; }
	int getPlayerArmies() { return *_playerArmies; }
	int getNumOfExchanges() { return *_numOfExchanges; }
	Strategy* getStrategy() { return _strategy; }

	// Setters.
	void setPlayerName(string& name);
	void setPlayerCountries(vector<Country*>& countries);
	void setPlayerDice(Dice& dice);
	void setPlayerCards(Hand& hand);
	void setPlayerArmies(int& armies);
	void setNumOfExchanges(int& exchanges);
	void setStrategy(Strategy* initStrategy);

	// Methods.
	void reinforce(); // Add armies to territories.
	void attack(); // Attack an adjacent player's armies.
	void fortify(); // Move own units from one country to another.
	void executeStrategy();
	void cheaper_attack();
	void removeall(vector<string> toberemoved);
	void removeit(Player* enemy, int location);
	void fortifycheater(vector<string> toberemoved);

};


void playerMain();