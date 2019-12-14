// Player file made by: Weiliang Xie (40100475).

#include <iostream>
#include "Player.h"
#include "Dice.h"
#include "Map.h"
#include "Cards.h"

using namespace std;


void playerMain() {

	cout << "\n---------------------------" << endl;
	cout << "Starting Player Driver: " << endl;
	cout << "---------------------------" << endl;

	// Creating player names.
	string name1 = "Player 1";
	string name2 = "Player 2";

	// Player dice.
	Dice d1;
	Dice d2;

	// Player countries.
	Country c1;
	Country c2;
	Country c3;
	Country c4;

	// Pushing in vector.
	vector<Country> p1Countries;

	p1Countries.push_back(c1);
	p1Countries.push_back(c2);
	p1Countries.push_back(c3);

	// Player 2 countries.
	vector<Country> p2Countries;
	p2Countries.push_back(c4);

	// Player hands.
	Hand h1;
	Hand h2;

	// Player armies.s
	int army1 = 10;
	int army2 = 5;

	// The number of times a player has exchanged cards.
	int exchange1 = 0;
	int exchange2 = 5;

	// Creating the players.
	//Player p(name1, p1Countries, d1, h1, army1, exchange1);
	//Player p2(name2, p2Countries, d2, h2, army2, exchange2);




	// Testing the methods.
	//p.reinforce();
	//p.attack();
	//p.fortify();

	cout << "Done!" << endl;
}