#include <iostream>
#include "Player.h"
#include "Dice.h"
#include "Cards.h"
#include "Map.h"
#include "GameEngine.h";
#include "GameObservers.h"
#include <algorithm>
#include<vector>
#include <exception>
using namespace std;

// Default constructor.
Player::Player() {
	_playerName = new string("No name");
	_playerCountries = new vector<Country*>();
	_playerDice = new Dice();
	_playerHand = new Hand();
	_playerArmies = new int(0);
	_numOfExchanges = new int(0);
	_strategy = new PlayerStrategy();
}

// Parameterized constructor.
Player::Player(string name, vector<Country*> countries, Dice  dice, Hand hand, int armies, int numOfExchanges, Strategy* strat) {
	_playerName = new string(name);
	_playerCountries = new vector<Country*>;

	// Deep copies.
	for (vector<Country*>::iterator it = countries.begin(); it != countries.end(); it++) {
		_playerCountries->push_back(new Country(**it));
	}

	_playerDice = new Dice(dice);
	_playerHand = new Hand(hand);
	_playerArmies = new int(armies);
	_numOfExchanges = new int(numOfExchanges);
	_strategy = strat;
}

Player::Player(const Player& p) {
	_playerName = new string(*p._playerName);
	_playerCountries = new vector<Country*>(*p._playerCountries);
	_playerDice = new Dice(*p._playerDice);
	_playerHand = new Hand(*p._playerHand);
	_playerArmies = new int(*p._playerArmies);
	_numOfExchanges = new int(*p._numOfExchanges);
	_strategy = p._strategy;
	_phaseObservers = p._phaseObservers;
}

void Player::operator=(const Player& p) {
	_playerName = new string(*p._playerName);
	_playerCountries = new vector<Country*>(*p._playerCountries);
	_playerDice = new Dice(*p._playerDice);
	_playerHand = new Hand(*p._playerHand);
	_playerArmies = new int(*p._playerArmies);
	_numOfExchanges = new int(*p._numOfExchanges);
	_strategy = p._strategy;
	_phaseObservers = p._phaseObservers;
}

// Default destructor.
Player::~Player() {

	delete _playerName;
	_playerName = nullptr;
	
	//We do not need to delete _player country since they are pointer to countries in the map
	// Deleting them would break the map
	_playerCountries = nullptr;

	delete _playerDice;
	_playerDice = nullptr;

	delete _playerHand;
	_playerHand = nullptr;

	delete _playerArmies;
	_playerArmies = nullptr;

	delete _numOfExchanges;
	_numOfExchanges = nullptr;
  
	//delete _strategy;
}

// Setters.
void Player::setPlayerName(string& name) {
	_playerName = new string(name);
}

void Player::setPlayerCountries(vector<Country*>& countries) {
	_playerCountries = new vector<Country*>(countries);

	// Deep copies.
	for (vector<Country*>::iterator it = countries.begin(); it != countries.end(); it++) {
		_playerCountries->push_back(new Country(**it));
	}
}

void Player::setPlayerDice(Dice& dice) {
	_playerDice = new Dice(dice);
}

void Player::setPlayerCards(Hand& hand) {
	_playerHand = new Hand(hand);
}

void Player::setPlayerArmies(int& armies) {
	_playerArmies = new int(armies);
}

void Player::setNumOfExchanges(int& numOfExchanges) {
	_numOfExchanges = new int(numOfExchanges);
}

void Player::setStrategy(Strategy* initStrategy) {
	_strategy = initStrategy;
}



// Methods
// Player chooses a country to which he wants to add armies to.
void Player::reinforce() {

	if (_strategy->proceed("reinforce")) {
		int numArmy = 0;
		int* numArmyPtr = &numArmy;
		int numcountry = _playerCountries->size();
		if (numcountry == 0) {
			cout << "Not available!" << endl;
		}
		else {
			numArmy = numcountry / 3;		//check number of country /3
			if (numArmy < 3) {
				numArmy = 3;
			}
			//check continent
			Map map;
			// need to link map
			int continentamount = continentscores();

			//check hand, make them ask which card to exchange.

			int exchangenum = exchangescore();
			numArmy += continentamount;
			numArmy += exchangenum;
			//reinforce2(numArmyPtr);
			_strategy->executeReinforce(_playerCountries, numArmy);
			// calling notify to display the phase
			notifyReinforce(_strategy->getarmynum(), _strategy->getname(), getPlayerName());

		}
	}
}

// Player chooses an adjacent player to attack.
void Player::attack() {
	Map* gps = GameEngine::gameboard->getMapPtr();
	vector<Country>* ads = gps->getListCountryPtr();

	vector<Player>* playerpointer = GameEngine::gameboard->getListPlayerPtr();
	Player* thisplayer = this;
	for (vector<Player>::iterator it = playerpointer->begin(); it != playerpointer->end(); it++) {
		if (*(it)->_playerName == *_playerName) {
			  thisplayer = &*(it);
		}
	}
	vector<Country*>* playercountriess = thisplayer->getPlayerCountriesPtr();
	vector<Country*> playercountrie = thisplayer->getPlayerCountries();
	vector<string> toberemoved = {};
	if (_strategy->proceed("attack")) {
		bool done = false;
		if (_strategy->proceed("cheater")) {
			cout << "cheater started attack" << endl;
			vector<Country> neigh;	
			Country* realOwn;
			Country* neighbour;
			//similar issue https://stackoverflow.com/questions/42641262/pop-back-causes-vector-subscript-out-of-range
			for (int i = 0; i < playercountriess->size(); i++) {
				realOwn = (playercountriess->at(i));
				cout << realOwn->getNameCountry() << endl;
				neigh = getEnemyNeighbours(*(playercountriess->at(i)));	//please check here.
				//it crashes in this location when captured country is realOwn it's because of getneighbour. couldn't fix the issue	
				for (int j = 0; j < neigh.size(); j++) {
					neighbour = &(neigh.at(j));
					//it is getting the list of enemy neighbor player and make a list
					if (neigh.at(j).getNamePlayer() != this->getPlayerName()) {
						toberemoved.push_back(neighbour->getNameCountry());
						//set name and put it to the player
						std::sort(toberemoved.begin(), toberemoved.end());
						auto it = std::unique(toberemoved.begin(), toberemoved.end());
						toberemoved.erase(it, toberemoved.end());
						cout << neighbour->getNameCountry() << "of country " << neighbour->getNamePlayer() << " name  is pusshed and cleanred. for testing" << endl;
						//above is removing the duplicated one.
					}

				}
				cout << "after inside for loop" << endl;
			}
			
			
			//here is for testing purpose. pls remove after.
			for (int i = 0; i < toberemoved.size(); ++i)
				std::cout <<  toberemoved[i] << " will be captured"<<endl;
			
			//function that conqure the list of countries.
			removeall(toberemoved);
			
			

			done = true;
			cout << "at the end" << endl;
			GameEngine::gameboard->getMapPtr()->changed();
			return;
		}

		while (!done) {
			displayCountries();
			Country* chosen = _playerCountries->at(_strategy->chooseOwnCountry(_playerCountries)); // Choose a source country.
			cout << "Choose a country to attack!" << endl;
			int result = 1;

			// Check to see if attack is valid.
			if (!hasEnemyNeighbours(*chosen)) {
				cout << "No neighbours available! Please choose again!" << endl;
				done = _strategy->continuePhase("attack", false);
			}
			else if (chosen->getNumArmies() < 2) {
				cout << "Not enough armies on that country! Please choose again!" << endl;
				done = _strategy->continuePhase("attack", false);
			}
			else {
				vector<Country> enemyCountries = getEnemyNeighbours(*chosen); // Get all neighbouring enemies.
				Country* attacked = &enemyCountries.at(_strategy->chooseCountry(enemyCountries)); // Choose one neighbouring enemy.

				Player* enemy = getEnemyPlayer(attacked->getNamePlayer());

				
				vector<int> ownRolls = _playerDice->play(_strategy->getNumOfDice(*chosen, "attack")); // Get the attacker's rolls.
				vector<int> enemyRolls = enemy->_playerDice->play(_strategy->getNumOfDice(*attacked, "defense")); // Get the defender's rolls.

				vector<int> numOfWins = compareRolls(ownRolls, enemyRolls); // Total wins from each.

				Country* realOwn = nullptr;

				// Allows us to get the "real" country and not just a copy.
				for (vector<Country*>::iterator it = _playerCountries->begin(); it != _playerCountries->end(); it++) {
					if ((*it)->getNameCountry() == chosen->getNameCountry())
						realOwn = *it;
				}

				// Set the number of armies after attack.
				realOwn->setNumArmies(realOwn->getNumArmies() - numOfWins.at(1));
				attacked->setNumArmies(attacked->getNumArmies() - numOfWins.at(0));
				
				
				// Attacker won the battle and gains a country.
				if (attacked->getNumArmies() <= 0) {
					attacked->setNumArmies(0);
					int location = 0;
					Player* enemy = getEnemyPlayer(attacked->getNamePlayer());
					vector<Country*> con = enemy->getPlayerCountries();
					vector<Country*>* con2 = enemy->getPlayerCountriesPtr();
					for (vector<Country*>::iterator it = con.begin(); it != con.end(); it++) {

						if (attacked->getNameCountry() == (*it)->getNameCountry()) {
							break;
						}
						location++;
					}
					attacked->setNamePlayer(*_playerName);
					//add it on player
					//playercountriess->push_back(attacked);	//edited
					playercountriess->push_back(new Country(*attacked));
					
					//remove it from the enemy
					//enemy->getPlayerCountriesPtr()->erase(enemy->getPlayerCountriesPtr()->begin() + location);
					enemy->getPlayerCountriesPtr()->erase(std::remove(enemy->getPlayerCountriesPtr()->begin(), enemy->getPlayerCountriesPtr()->end(), attacked), enemy->getPlayerCountriesPtr()->end());


					Map* gps = GameEngine::gameboard->getMapPtr();
					vector<Country>* ads = gps->getListCountryPtr();
					for (vector<Country>::iterator it = ads->begin(); it != ads->end(); it++) {
						if (it->getNameCountry() == attacked->getNameCountry()) {
							it->setNamePlayer(*_playerName);
						}
					}

					//ads->erase(location);
					enemy->displayCountries();

					cout << *_playerName << " won the attack!" << endl;

					int locationofPlayer = 0;
					for (vector<Player>::iterator it = playerpointer->begin(); it != playerpointer->end(); it++) {
						if (enemy->getPlayerName() == *(it->_playerName)) {
							if (enemy->getPlayerCountries().size() == 0) {
								cout << enemy->getPlayerName() << " lost all their countries! You lose! Please leave!" << endl;
							}
							break;
						}
						locationofPlayer++;
					}
					if (enemy->getPlayerCountries().size() == 0) {
						playerpointer->erase(playerpointer->begin() + locationofPlayer);
						//this is correct way
						//playerpointer->erase(std::remove(playerpointer->begin(), playerpointer->end(), *enemy), playerpointer->end());

					}

					// Move the armies.
					int move = _strategy->numOfArmiesToMove(*realOwn);
					_playerCountries->back()->setNumArmies(move);
					cout << "number of army in the new country is " << _playerCountries->back()->getNumArmies() << endl;
					realOwn->setNumArmies(realOwn->getNumArmies() - move);	//edited.
				}
				else {
					result = 0;
				}
				
				done = _strategy->continuePhase("attack", true);
				// calling notify to display the phase
				notifyAttack(chosen->getNameCountry(), attacked->getNameCountry(), enemy->getPlayerName(), result, realOwn->getNumArmies(), realOwn->getNameCountry(), attacked->getNumArmies(), getPlayerName());
			}
		}
	}
	GameEngine::gameboard->getMapPtr()->changed();
}


//from the enemy list, it conqure them and put it in the player's list
void Player::removeall(vector<string> toberemoved) {
	Map* gps = GameEngine::gameboard->getMapPtr();
	vector<Country>* ads = gps->getListCountryPtr();
		
	vector<Player>* playerpointer = GameEngine::gameboard->getListPlayerPtr();
	Player* thisplayer = this;
	for (vector<Player>::iterator it = playerpointer->begin(); it != playerpointer->end(); it++) {
		if (*(it)->_playerName == *_playerName) {
			thisplayer = &*(it);
		}
	}
	vector<Country*>* playercountriess = thisplayer->getPlayerCountriesPtr();
	vector<Country*> playercountrie = thisplayer->getPlayerCountries();


	for(int i =0; i<toberemoved.size(); i++){
		string a = toberemoved[i];
		Player* enemy = nullptr;
		Country* countrys = nullptr;
		for (vector<Country>::iterator it = ads->begin(); it != ads->end(); it++) {
			if (a == (it->getNameCountry())) {
				enemy = getEnemyPlayer((*it).getNamePlayer());
				countrys = &*it;
			}
		}
		

		vector<Country*> con = enemy->getPlayerCountries();
		int location = 0;
		Country* tobedeleted = nullptr;
		for (vector<Country*>::iterator its = con.begin(); its != con.end(); its++) {
			if (a == (*its)->getNameCountry()) {
				tobedeleted = *its;
				break;
			}
			location++;
		}
		//removing from the enemy
		cout <<  a <<" is conqured! "  << endl;
		//another way: enemy->getPlayerCountriesPtr()->erase(enemy->getPlayerCountriesPtr()->begin() + location);
		vector<Country*>* vec = enemy->getPlayerCountriesPtr();
		vec->erase(std::remove(vec->begin(), vec->end(), tobedeleted),vec->end());

		//adding on player
		countrys->setNamePlayer(*_playerName);
		playercountriess->push_back(new Country(*countrys));

		//modify name once again from the map.
		for (vector<Country>::iterator it = ads->begin(); it != ads->end(); it++) {
			if (it->getNameCountry() == countrys->getNameCountry()) {
				(&*it)->setNamePlayer(*_playerName);
			}
		}

		//when enemy lost all country, remove them.
		int locationofPlayer = 0;

		for (vector<Player>::iterator it = playerpointer->begin(); it != playerpointer->end(); it++) {
			if (enemy->getPlayerName() == *(it->_playerName)) {
				if (enemy->getPlayerCountries().size() == 0) {
					cout << enemy->getPlayerName() << " lost all their countries! You lose! Please leave!" << endl;
				}
				break;
			}
			locationofPlayer++;
		}
		if (enemy->getPlayerCountries().size() == 0) {
			playerpointer->erase(playerpointer->begin() + locationofPlayer);
		}	
	}


}
// Compares the rolls pairwise. Returns the number of wins by each player.
vector<int> Player::compareRolls(vector<int> ownRolls, vector<int> defenseRolls) {
	bool done = false;
	int ownCounter = 0; // Counts the attacker's wins.
	int defenseCounter = 0; // Counts the defender's wins.

	vector<int>::iterator ownIt = ownRolls.begin();
	vector<int>::iterator defenseIt = defenseRolls.begin();

	while (!done) {

		// Attack wins.
		if (*ownIt > *defenseIt) {
			cout << "Attack won roll: ";
			cout << *ownIt << " > " << *defenseIt << endl;
			ownCounter++;
		}
		else { // Defense wins.
			cout << "Defense won roll: ";
			cout << *defenseIt << " > " << *ownIt << endl;
			defenseCounter++;
		}

		// Keep comparing pairwise unless done.
		if (ownCounter == ownRolls.size() || defenseCounter == defenseRolls.size() || (ownCounter + defenseCounter) >= ownRolls.size() ||
			(ownCounter + defenseCounter) >= defenseRolls.size() || ownIt == ownRolls.end() || defenseIt == defenseRolls.end())
			done = true;

		// Increment iterators.
		ownIt++;
		defenseIt++;
	}

	// Push the number of wins. First index is attacker's wins, second is defender's.
	vector<int> numOfWins;
	numOfWins.push_back(ownCounter);
	numOfWins.push_back(defenseCounter);

	return numOfWins;
}

// Get the number of dice to be rolled.
int Player::getNumOfDice(Country& c, string type) {
	int numOfDice = 0;
	bool check = false;
	
	do {
		if (type == "defense") {
			if (c.getNumArmies() == 0) {
				cout << "you have no army so you can roll only once" << endl;
				return 1;
			}
		}
		cout << "How many dice will " << c.getNamePlayer() << " roll? (" << c.getNameCountry() << " has " << c.getNumArmies() << " armies): ";
		cin >> numOfDice;
		check = false;
		

		// Invalid number.
		if (numOfDice < 0 || ((numOfDice > c.getNumArmies()) || (type == "attack" ? (numOfDice > 3) : (numOfDice > 2)))) {
			cout << "Invalid number of dice. Please try again." << endl;
			check = true;
		}
	
		
	} while (check);

	return numOfDice;
}

// Player moves armies from one country to an adjacent country under his control.
void Player::fortify() {

	Map* gps = GameEngine::gameboard->getMapPtr();
	vector<Country>* ads = gps->getListCountryPtr();

	vector<Player>* playerpointer = GameEngine::gameboard->getListPlayerPtr();
	Player* thisplayer = this;
	for (vector<Player>::iterator it = playerpointer->begin(); it != playerpointer->end(); it++) {
		if (*(it)->_playerName == *_playerName) {
			thisplayer = &*(it);
		}
	}
	vector<Country*>* playercountriess = thisplayer->getPlayerCountriesPtr();
	vector<Country*> playercountrie = thisplayer->getPlayerCountries();
	vector<string> upgrade;
	
	if (_strategy->proceed("fortify")) {
		//i disabled the fortify, please edit back to done==false, proceed("cheater), 
		//first we have to fix the issue in attack, 
		// it will fix the issue in fortify. it is following the same logic.
		bool done = true;
		if (_strategy->proceed("cheatereee")) {
			cout << "cheater fortify phase started" << endl;
			vector<Country> neigh;
			Country* realOwn;
			Country* neighbour;
			try {
				for (vector<Country*>::iterator it = playercountriess->begin(); it != playercountriess->end(); it++) {
					neigh = getEnemyNeighbours(**it);
					realOwn = *it;//current country
					//current neighbours
					for (vector<Country>::iterator its = neigh.begin(); its != neigh.end(); its++) {
						neighbour = &*its;
						if (its->getNamePlayer() != this->getPlayerName()) {
							realOwn = *it;
							cout << realOwn->getNameCountry() << " is being saved in the list owner:" << endl;
							upgrade.push_back(realOwn->getNameCountry());
							//cout << "Captured " << neighbour->getNameCountry() << "." << endl;
							//set name and put it to the player
							std::sort(upgrade.begin(), upgrade.end());
							auto it = std::unique(upgrade.begin(), upgrade.end());
							upgrade.erase(it, upgrade.end());
						}
					}
				}


				cout << "will be fortifying it soon" << endl;
				for (int i = 0; i < upgrade.size(); ++i)
					std::cout << upgrade[i] << " will be fortified" << endl;
				fortifycheater(upgrade);
			}
			catch (exception & e) {
				cout << "will be fortifying i" << endl;
				fortifycheater(upgrade);
			}



			done = true;
		}
		// Keep looping until done.
		while (!done) {
			cout << "Choose a source country: " << endl;
			displayCountries(); // Display the player's countries.
			Country* chosen = _playerCountries->at(_strategy->chooseOwnCountry(_playerCountries));

			// Check validity before mobilizing armies.
			if (chosen->getNumArmies() <= 1) {
				cout << "No available armies to move." << endl;
				done = _strategy->continuePhase("fortify", false);
			}
			else if (!hasFriendlyNeighbours(*chosen)) { // No neighbours.
				cout << "No friendly neighbours!" << endl;
				done = _strategy->continuePhase("fortify", false);
			}
			else {
				vector<Country> friendlyNeighbours = getFriendlyNeighbours(*chosen); // Keep track of friendly neighbours.
				Country friendly = friendlyNeighbours.at(_strategy->chooseCountry(friendlyNeighbours)); // Get the country.

				Country* real = nullptr;

				// Allows us to get the "real" country to fortify and not just a copy.
				for (vector<Country*>::iterator it = _playerCountries->begin(); it != _playerCountries->end(); it++) {
					if ((*it)->getNameCountry() == friendly.getNameCountry())
						real = *it;
				}

				int toMove = _strategy->numOfArmiesToMove(*chosen);

				// Change the number of armies.
				real->setNumArmies(real->getNumArmies() + toMove);
				chosen->setNumArmies(chosen->getNumArmies() - toMove);


				done = _strategy->continuePhase("fortify", false);
				
				// calling notify to display the phase
				notifyFortify(chosen->getNameCountry(), friendly.getNameCountry(), chosen->getNumArmies(), real->getNumArmies(), getPlayerName());

				real = nullptr;
				chosen = nullptr;
			}
		}
	}
}
void Player::fortifycheater(vector<string> upgrade) {

	Map* gps = GameEngine::gameboard->getMapPtr();
	vector<Country>* ads = gps->getListCountryPtr();

		for (int i = 0; i < upgrade.size(); i++) {
		string a = upgrade[i];
		//Player* enemy = nullptr;
		Country* countrys = nullptr;
		for (vector<Country>::iterator it = ads->begin(); it != ads->end(); it++) {
			if (a == (it->getNameCountry())){
			countrys = &*it;
			cout << "testing name of country " << countrys->getNamePlayer() << endl;
			countrys->setNumArmies(countrys->getNumArmies()*2); 
			}
		}

	}
}

// Find an enemy player with the given name.
Player* Player::getEnemyPlayer(string enemyName) {
	Player* enemy = nullptr;

	// Find the enemy player within all the game players.
	for (vector<Player>::iterator it = GameEngine::gameboard->getListPlayerPtr()->begin(); it != GameEngine::gameboard->getListPlayerPtr()->end(); it++) {
		if (enemyName == *(it->_playerName))
			enemy = &(*it);
	}

	// Didn't find enemy (Shouldn't happen).
	if (enemy == nullptr) {
		cout << "Error." << endl;
		return nullptr;
	}

	return enemy;
}

// Choose the country to fortify.
int Player::chooseCountryAttack(int size) {
	int choice;

	do {
		cout << "Choose country to attack: ";
		cin >> choice;
		if (choice <= 0 || choice > size)
			cout << "Invalid choice. Please try again." << endl;
	}
	while (choice <= 0 || choice > size);

	return choice - 1;
}

// Check if the attacking country has neighbours it can attack.
bool Player::hasEnemyNeighbours(Country& c) {
	vector<Country> allNeighbours = GameEngine::gameboard->getMapPtr()->getNeighbours(c);

	int counter = 0;
	int i = 1;

	for (vector<Country>::iterator it = allNeighbours.begin(); it != allNeighbours.end(); it++) {
		
		if (it->getNamePlayer() != *_playerName) {
			cout << i << ". " << it->getNameCountry() << " (" << it->getNamePlayer() << ")" << endl;
			i++;
			counter++;
		}
	}

	return (counter != 0);
}


// Return all enemy neighbours.
vector<Country> Player::getEnemyNeighbours(Country& c) {

	vector<Country> allNeighbours = GameEngine::gameboard->getMapPtr()->getNeighbours(c); // it gets error here from the second turn.
	vector<Country> enemyNeighbours; // Keep only the friendly neighbours.
	
	// Choose only enemy neighbours.
	cout << "locating 1" << endl;
	for (vector<Country>::iterator it = allNeighbours.begin(); it != allNeighbours.end(); it++) {
		cout << *_playerName <<"  "<< it->getNamePlayer() << endl;
		if (it->getNamePlayer() != *_playerName) {
			cout <<"enemy  pushed"<< *_playerName << "  " << it->getNamePlayer() << endl;
			enemyNeighbours.push_back(*it);
		}

	}

	return enemyNeighbours;
}



// Keep track of whether the user wants to quit the phase.
bool Player::continuePhase() {
	bool choiceLoop = false;
	bool done = false;

	while (!choiceLoop) {
		cout << "Would you like to quit? (y/n): ";
		string choice;
		cin >> choice;

		if (choice == "y") {
			choiceLoop = true;
			done = true;
		}
		else if (choice == "n") {
			choiceLoop = true;
			done = false;
		}
		else {
			choiceLoop = false;
		}
	}

	return done;
}

// Checks whether the player has any available friendly neigbouring countries.
bool Player::hasFriendlyNeighbours(Country& c) {
	const vector<Country>& allNeighbours = GameEngine::gameboard->getMapPtr()->getNeighbours(c);

	int counter = 0; // Keep track of the number.
	int i = 1; // For display purposes.

	cout << "Here are the friendly neighbours of " << c.getNameCountry() << ":" << endl;

	// Display friendly neighbours.
	for (vector<Country>::const_iterator it = allNeighbours.begin(); it != allNeighbours.end(); it++) {
		if (it->getNamePlayer() == *_playerName && it->getNameCountry() != c.getNameCountry()) {
			cout << i << ". " << it->getNameCountry() << endl;
			i++;
			counter++;
		}
	}

	return counter != 0; // Means that there are more than 0 friendly neighbours.
}

// Get a list of all the friendly neighbouring countries.
vector<Country> Player::getFriendlyNeighbours(Country& c) {
	vector<Country> allNeighbours = GameEngine::gameboard->getMapPtr()->getNeighbours(c); // Get all neighbours.
	vector<Country> friendlyNeighbours; // Keep only the friendly neighbours.

	// Choose only friendly neighbours.
	for (vector<Country>::iterator it = allNeighbours.begin(); it != allNeighbours.end(); it++) {
		if (it->getNamePlayer() == *_playerName && it->getNameCountry() != c.getNameCountry()) {
			friendlyNeighbours.push_back(*it);
		}
	}

	return friendlyNeighbours;
}

// Decide whether to start the phase or not.
bool Player::choice() {
	char choice;

	do {
		cout << "Will you proceed? (y/n): ";
		cin >> choice;

		// Make sure it's a valid choice.
		if (choice != 'y' && choice != 'n')
			cout << "Invalid identifier. Please try again." << endl;
	}
	while (choice != 'y' && choice != 'n'); // Keep looping until it's valid.

	return (choice == 'y');
}

// Display list a of the player's countries and the number of armies.
void Player::displayCountries() {
	int i = 1;

	cout << "Your countries: " << endl;
	for (vector<Country*>::iterator it = _playerCountries->begin(); it != _playerCountries->end(); it++) {
		cout << i++ << ". " <<(*it)->getNameCountry() << " (" << (*it)->getNumArmies() << ((*it)->getNumArmies() == 1 ? " army" : " armies") << ")." << endl;
	}
}

// Choose the country to attack with.
int Player::chooseOwnCountry() {
	int chosenCountryIndex;

	do {
		cout << "Please choose the country you want to attack with: ";
		cin >> chosenCountryIndex;

		// Check validity of choice.
		if (chosenCountryIndex > _playerCountries->size() || chosenCountryIndex < 1)
			cout << "Invalid country choice. Please try again." << endl;

	}
	while (chosenCountryIndex > _playerCountries->size() || chosenCountryIndex < 1);

	return chosenCountryIndex - 1;
}

// Choose the country to fortify.
int Player::chooseCountryFortify(int size) {
	int choice;

	do {
		cout << "Choose country to fortify: ";
		cin >> choice;
		if (choice <= 0 || choice > size)
			cout << "Invalid choice. Please try again." << endl;
	}
	while (choice <= 0 || choice > size);

	return choice - 1;
}

// Choose a country to fortify.
int Player::chooseSourceCountry() {
	int chosenCountryIndex;

	do {
		cout << "Please choose a source country: ";
		cin >> chosenCountryIndex;

		// Check validity of choice.
		if (chosenCountryIndex > _playerCountries->size() || chosenCountryIndex < 1)
			cout << "Invalid country choice. Please try again." << endl;

	}
	while (chosenCountryIndex > _playerCountries->size() || chosenCountryIndex < 1);

	return chosenCountryIndex - 1; // Displayed indexes start at 1.
}

// Mobilize the chosen number of armies.
int Player::numOfArmiesToMove(Country& c) {
	int numToMove;

	do {
		cout << "Enter the number of armies you want to move (" << c.getNameCountry() << " has " << c.getNumArmies() << " armies): ";
		cin >> numToMove;

		if (numToMove < 0 || numToMove > c.getNumArmies() )
			cout << "Invalid number of armies. Please try again." << endl;
	}
	while (numToMove <= 0 || numToMove > c.getNumArmies() ); // Check validity.

	c.setNumArmies(c.getNumArmies() - numToMove); // Remove from source country.

	return numToMove; // Need to add to fortified country.
}

void Player::reinforce2(int* numArmyPtr) {

	int numcountry = _playerCountries->size();
	cout << "Your available number of armies is: " << *numArmyPtr << endl;
	while (*numArmyPtr > 0) {

		int count = 1;

		for (vector<Country*>::iterator it = _playerCountries->begin(); it != _playerCountries->end(); it++) {
			cout << count << ".  " << (*it)->getNameCountry() << " has " << (*it)->getNumArmies() << " troops." << endl;
			count++;
		}

		cout << "Select where to put the army: ";
		int wheretoput;
		cin >> wheretoput;

		this->placeit(_playerCountries->at(wheretoput - 1), numArmyPtr);
	}
}
void Player::placeit(Country* cntry, int* numArmy) {
	cout << "Enter the number of armies you want to put: ";
	int num;
	cin >> num;
	if (*numArmy == 0) {
		cout << "Finished!" << endl;
	}
	if (num > * numArmy) {
		cout << "You don't have that many!" << endl;
	}
	if (num <= *numArmy) {
		cout << "Armies before reinforcement (" << cntry->getNameCountry() << "): " << cntry->getNumArmies() << endl;
		int previous = cntry->getNumArmies();
		cntry->setNumArmies(previous + num);
		cout << "Armies after reinforcement(" << cntry->getNameCountry() << "): " << cntry->getNumArmies() << endl;
		*numArmy = *numArmy - num;
		cout << "Number of armies left to place: " << *numArmy << endl;
	}
}

int Player::continentscores() {
	cout << "Continent info: " << endl;
	vector<Continent>* continents = GameEngine::gameboard->getMapPtr()->getListContinentPtr();
	bool check = false;
	int score = 0;
	for (int i = 0; i < continents->size(); i++) {
		vector<Country>* countries = continents->at(i).getListCountryPtr();
		int valueofCountry = continents->at(i).getNumOfArmies();
		for (size_t j = 0; j < countries->size(); j++) {
			if (countries->at(j).getNamePlayer() == *_playerName) {
				check = true;
			}
			else {
				check = false;
			}
		}
		if (check) {
			score += valueofCountry;
		}
	}
	cout << "The continent has: " << score << " armies." << endl;
	return score;
}

int Player::exchangescore() {
	bool check = false;
	vector<Card>* cards = _playerHand->getHandPtr();
	int exchangenum = 0;
	Deck* deckObj12 = GameEngine::gameboard->getDeckOfCardPtr();
	//int exchangenumber = *_numOfExchanges;

	if (*_numOfExchanges == 0) {
		(*_numOfExchanges)++;
	}
	cout << "Current cards :" << endl;
	if (_playerHand->getHandPtr()->size() < 3) {
		cout << "You don't have enough card to exchange!" << endl;
	}
	if (_playerHand->getHandPtr()->size() == 3 || cards->size() == 4) {
		cout << "Do you want to exchange cards? (y/n)" << endl;
		string a;
		cin >> a;
		if (a == "y") {
			check = true;
		}
	}
	if (_playerHand->getHandPtr()->size() == 5 || cards->size() == 6) {
		cout << "You need to exchange!" << endl;
		check = true;
	}
	if (_playerHand->getHandPtr()->size() > 6) {
		cout << "Too many cards!" << endl;
		check = true;
	}
	int count = 1;
	if (check) {
		for (vector<Card>::iterator it = _playerHand->getHandPtr()->begin(); it != _playerHand->getHandPtr()->end(); it++) {
			Card c = *it;
			int* n = c.type;
			cout << count << ". " << *n << endl;
			count++;
		}

		cout << "Select 3 cards that you want to exchange (Enter the number and press enter):" << endl;
		int one;
		int two;
		int three;
		cin >> one;
		cin >> two;
		cin >> three;

		int num = _playerHand->exchange(_playerHand->getHandPtr()->at(one - 1), _playerHand->getHandPtr()->at(two - 1), _playerHand->getHandPtr()->at(three - 1), *_numOfExchanges, *GameEngine::gameboard->getDeckOfCardPtr());
		exchangenum = num;
		cout << "The number of armies gained from the exchange is: " << exchangenum << endl;
	}

 	return exchangenum;
}





