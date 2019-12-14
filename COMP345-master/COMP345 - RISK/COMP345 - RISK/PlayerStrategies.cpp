#include <iostream>
#include "PlayerStrategies.h"
#include "Map.h"
#include "Player.h"
using namespace std;

// Non-virtual function.
int Strategy::getNumOfDice(Country& c, string type) {
	return 0;
}

// Player can choose whether to proceed with the phase or not.
bool PlayerStrategy::proceed(string phase) {
	char choice;

	do {
		cout << "Will you proceed with " << phase << "? (y/n): ";
		cin >> choice;

		// Make sure it's a valid choice.
		if (choice != 'y' && choice != 'n')
			cout << "Invalid identifier. Please try again." << endl;
	}
	while (choice != 'y' && choice != 'n'); // Keep looping until it's valid.

	return (choice == 'y');
}

// Player can choose which of his countries to reinforce.
int PlayerStrategy::chooseOwnCountry(vector<Country*>* countries) {
	int chosenCountryIndex;

	do {
		cout << "Please choose a country you own: ";
		cin >> chosenCountryIndex;

		// Check validity of choice.
		if (chosenCountryIndex > countries->size() || chosenCountryIndex < 1)
			cout << "Invalid country choice. Please try again." << endl;

	}
	while (chosenCountryIndex > countries->size() || chosenCountryIndex < 1);

	return chosenCountryIndex - 1;
}

// Player can choose whether to continue with the phase or not.
bool PlayerStrategy::continuePhase(string phase, bool canContinue) {
	bool choiceLoop = false;
	bool done = false;

	while (!choiceLoop) {
		cout << "Would you like to quit " << phase << "? (y/n): ";
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

// Player can choose which country to attack.
int PlayerStrategy::chooseCountry(vector<Country> countries) {
	int choice;
	int size = countries.size();

	do {
		cout << "Choose country: ";
		cin >> choice;
		if (choice <= 0 || choice > size)
			cout << "Invalid choice. Please try again." << endl;
	}
	while (choice <= 0 || choice > size);

	return choice - 1;
}

// Human player can choose how many dice to play.
int PlayerStrategy::getNumOfDice(Country& c, string type) {
	int numOfDice = 0;
	bool check = false;

	do {
		// Defense.
		if (type == "defense") {
			if (c.getNumArmies() == 0) {
				cout << "you have no army so you can roll only once" << endl;
				return 1;
			}
		}
		cout << "How many dice will " << c.getNamePlayer() << " roll? (" << c.getNameCountry() << " has " << c.getNumArmies() << " armies): ";
		cin >> numOfDice; // Player choice.
		check = false;
		

		// Invalid number.
		if (numOfDice < 0 || ((numOfDice > c.getNumArmies()) || (type == "attack" ? (numOfDice > 3) : (numOfDice > 2)))) {
			cout << "Invalid number of dice. Please try again." << endl;
			check = true;
		}
	}
	while (check);

	return numOfDice; // Number of dice chosen.
}

int PlayerStrategy::numOfArmiesToMove(Country& c) {		
	int numToMove;

	do {
		cout << "Enter the number of armies you want to move (" << c.getNameCountry() << " has " << c.getNumArmies() << " armies): ";
		cin >> numToMove;

		if (numToMove < 0 || numToMove > c.getNumArmies())
			cout << "Invalid number of armies. Please try again." << endl;
	}
	while (numToMove <= 0 || numToMove > c.getNumArmies()); // Check validity.

	c.setNumArmies(c.getNumArmies() - numToMove); // Remove from source country.

	return numToMove; // Need to add to fortified country.
}

// Human player can choose which country to reinforce.
int PlayerStrategy:: executeReinforce(vector<Country*>* countries, int a) {
	cout << "Your available number of armies is: " << a << endl;
	while (a > 0) {

		int count = 1;// check if it should be 0 or 1

		for (vector<Country*>::iterator it = countries->begin(); it != countries->end(); it++) {
			cout << count << ".  " << (*it)->getNameCountry() << " has " << (*it)->getNumArmies() << " troops." << endl;
			count++;
		}

		cout << " select where to put: ";
		int wheretoput;
		cin >> wheretoput;
		name=countries->at(wheretoput - 1)->getNameCountry();
		placeit(countries->at(wheretoput - 1), &a);
	}
	return 0;
}

// Place the given amount of armies in the chosen country.
void PlayerStrategy::placeit(Country* cntry, int* numArmy) {
	cout << "Enter the number of armies you want to put: ";
	int num;
	cin >> num;
	armynum = num;
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

// Always reinforce the strongest country.
int AggressiveStrategy::executeReinforce(vector<Country*>* countries, int a) {
	cout << "Your available number of armies is: " << a << endl;

	if (a > 0) {
		int count = 0;
		Country* strong = countries->at(0);

		// Display all countries.
		for (vector<Country*>::iterator it = countries->begin(); it != countries->end(); it++) {
			cout << count << ".  " << (*it)->getNameCountry() << " has " << (*it)->getNumArmies() << " troops." << endl;
			
			// Find the strongest country.
			if ((*it)->getNumArmies() > strong->getNumArmies()) {
				strong = countries->at(count);
			}
			count++;
		}

		cout << "Keep reinforcing the strongest country!" << endl;
		name = strong->getNameCountry();
		armynum = a;
		placeit(strong, &a); // Place the armies onto the strongest country.
	}
	
	return 0;
}


void AggressiveStrategy::placeit(Country* cntry, int* numArmy) {
	cout << "every army is being putted "<<endl;
		cout << "Armies before reinforcement (" << cntry->getNameCountry() << "): " << cntry->getNumArmies() << endl;
		int previous = cntry->getNumArmies();
		cntry->setNumArmies(previous + *numArmy);
		cout << "Armies after reinforcement(" << cntry->getNameCountry() << "): " << cntry->getNumArmies() << endl;
}

// Aggressive player always starts the phase.
bool AggressiveStrategy::proceed(string phase) {
	return(phase == "attack" || phase == "reinforce" || phase == "fortify");
}


//insert the observer pattern here too for attack.
int AggressiveStrategy::chooseOwnCountry(vector<Country*>* countries) {
	Country* strong = countries->at(0);
	int count = 0;
	static int lastPosition;
	int position = 0;

	for (vector<Country*>::iterator it = countries->begin(); it != countries->end(); it++) {

		if ((*it)->getNumArmies() > strong->getNumArmies()) {

			position = count;
			strong = countries->at(position);
		}
		count++;
	}

	return position;
}

bool AggressiveStrategy::continuePhase(string phase, bool canContinue) {
	if (canContinue) {
		cout << "Continuing " << phase << "!" << endl;
		return false;
	}
	else
		return true;
}


// Choose a given country with the given vector of countries.
int AggressiveStrategy::chooseCountry(vector<Country> countries) {
	int mostArmies = countries.at(0).getNumArmies();
	int count = 0;
	int position = 0;
	for (vector<Country>::iterator it = countries.begin(); it != countries.end(); it++) {

		if (it->getNumArmies() > mostArmies) {

			position = count;
			mostArmies = it->getNumArmies();
		}
		count++;
	}

	return position; // Return where the country is located in the vector.
}


// Aggressive player always rolls the most dice possible.
int AggressiveStrategy::getNumOfDice(Country& c, string type) {

	// Aggressive player is on the defense.
	if (type == "defense") {
		if (c.getNumArmies() < 2) {
			cout << "You can only roll 1!" << endl;
			return 1;
		} else {
			return 2;
		}
	}

	// Attack with maximum aggression.
	cout << "Maxmimum aggression!" << endl;
	if (c.getNumArmies() > 3)
		return 3;
	
	return c.getNumArmies(); // Number of dice to roll.
}


// Always move the most armies they can.
int AggressiveStrategy::numOfArmiesToMove(Country& c) {
	int numarmy = 0;
	numarmy = c.getNumArmies() - 1;
	cout << "number of army to move   " << numarmy << endl;
	return numarmy;
}


// Benevolent never attacks.
bool BenevolentStrategy::proceed(string phase) {
	if (phase == "reinforce" || phase == "fortify") {
		return true;
	}
	else if (phase == "attack") {
		cout << "Will not attack!" << endl;
		return false;
	}
}


// Benevolent always chooses the strongest country to fortify with.
int BenevolentStrategy::chooseOwnCountry(vector<Country*>* countries) {
	Country* strong = countries->at(0);
	static int lastPosition; // Keep track of the last position.
	int count = 0;
	int position = 0;

	// Find the army with the most armies.
	for (vector<Country*>::iterator it = countries->begin(); it != countries->end(); it++) {

		// Found a new strongest.
		if ((*it)->getNumArmies() > strong->getNumArmies()) {
			position = count;
			strong = countries->at(position);
		}

		// Avoids some edge cases where the player breaks.
		if (position == lastPosition) {
			position = count;
			strong = countries->at(position + 1);
		}
		count++;
	}

	cout << strong->getNameCountry() << " is your strongest country!" << endl;

	lastPosition = position; // Change the last position.

	return position;
}


// Benevolent player continues.
bool BenevolentStrategy::continuePhase(string phase, bool canContinue) {
	if (canContinue) {
		cout << "Continuing " << phase << "!" << endl;
		return false;
	}
	
	else
		return true;
}

// Only move 1 country at a time.
int BenevolentStrategy::numOfArmiesToMove(Country& c) {
	cout << "Moving from " << c.getNameCountry() << "!" << endl;
	return 1;
}


// Choose the country with the least armies.
int BenevolentStrategy::chooseCountry(vector<Country> countries) {
	int leastArmies = countries.at(0).getNumArmies();
	int count = 0;
	int position = 0;

	// Find the weakest army.
	for (vector<Country>::iterator it = countries.begin(); it != countries.end(); it++) {
		if (it->getNumArmies() < leastArmies) {

			position = count;
			leastArmies = it->getNumArmies();
		}
		count++;
	}

	return position;
}


// Always reinforce the weakest armies.
int BenevolentStrategy::executeReinforce(vector<Country*>* countries, int a) {
	cout << "Your available number of armies is: " << a << endl;

	if (a > 0) {

		int count = 0;
		Country* weak = countries->at(0);

		// Display and find the weakest army.
		for (vector<Country*>::iterator it = countries->begin(); it != countries->end(); it++) {
			cout << count << ".  " << (*it)->getNameCountry() << " has " << (*it)->getNumArmies() << " troops." << endl;

			if ((*it)->getNumArmies() < weak->getNumArmies()) {

				weak = countries->at(count);

			}
			count++;
		}

		cout << " Reinforcing a weak country!" << endl;
		name = weak->getNameCountry();
		armynum = a;
		placeit(weak, &a);
	}

	return 0;
}

// Helper function.
void BenevolentStrategy::placeit(Country* cntry, int* numArmy) {
	cout << "Armies before reinforcement (" << cntry->getNameCountry() << "): " << cntry->getNumArmies() << endl;
	int previous = cntry->getNumArmies();
	cntry->setNumArmies(previous + *numArmy);
	cout << "Armies after reinforcement(" << cntry->getNameCountry() << "): " << cntry->getNumArmies() << endl;
}

//===============================

// Always reinforce the strongest country.
int CheaterStrategy::executeReinforce(vector<Country*>* countries, int a) {
	cout << "Cheapter: All  armies have doubled " << endl;

	if (a > 0) {
		int count = 0;

		
		// Display all countries.
		for (vector<Country*>::iterator it = countries->begin(); it != countries->end(); it++) {
			(*it)->setNumArmies((*it)->getNumArmies() * 2);
			cout << count << ".  " << (*it)->getNameCountry() << " has " << (*it)->getNumArmies() << " troops." << endl;
			count++;
			
		}
	
		
		
	}

	return 0;
}
void CheaterStrategy::placeit(Country* cntry, int* numArmy) {
	cout << "Armies before reinforcement (" << cntry->getNameCountry() << "): " << cntry->getNumArmies() << endl;
	int previous = cntry->getNumArmies();
	cntry->setNumArmies(previous + *numArmy);
	cout << "Armies after reinforcement(" << cntry->getNameCountry() << "): " << cntry->getNumArmies() << endl;
}


// Aggressive player always starts the phase.
bool CheaterStrategy::proceed(string phase) {
	return(phase == "cheater"||phase == "attack" || phase == "reinforce" || phase == "fortify");
}


//insert the observer pattern here too for attack.
int CheaterStrategy::chooseOwnCountry(vector<Country*>* countries) {
	Country* strong = countries->at(0);
	int count = 0;
	static int lastPosition;
	int position = 0;

	for (vector<Country*>::iterator it = countries->begin(); it != countries->end(); it++) {

		if ((*it)->getNumArmies() > strong->getNumArmies()) {

			position = count;
			strong = countries->at(position);
		}
		count++;
	}

	return position;
}

bool CheaterStrategy::continuePhase(string phase, bool canContinue) {
	if (canContinue) {
		cout << "Continuing " << phase << "!" << endl;
		return false;
	}
	else
		return true;
}


// Choose a given country with the given vector of countries.
int CheaterStrategy::chooseCountry(vector<Country> countries) {
	int mostArmies = countries.at(0).getNumArmies();
	int count = 0;
	int position = 0;
	for (vector<Country>::iterator it = countries.begin(); it != countries.end(); it++) {

		if (it->getNumArmies() > mostArmies) {

			position = count;
			mostArmies = it->getNumArmies();
		}
		count++;
	}

	return position; // Return where the country is located in the vector.
}


// Always move the most armies they can.
int CheaterStrategy::numOfArmiesToMove(Country& c) {
	int numarmy = 1;
	if(c.getNumArmies()!=0)
	numarmy = c.getNumArmies() - 1;

	cout << "number of army to move   " << numarmy << endl;
	return numarmy;
}

