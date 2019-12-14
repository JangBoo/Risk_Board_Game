#include "Cards.h"
#include "Dice.h"
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include "GameEngine.h"

//void setup() {
//	Player::gameMap = Player::setMap();
//	Player::gameDeck = new Deck(50);
//}
//
//void methodDriver() {
//	setup();
//	// Creating player names.
//
//	string name1 = GameBoard::_listPlayer->at(0).getPlayerName();
//	string name2 = GameBoard::_listPlayer->at(1).getPlayerName();
//
//
//	// Player dice.
//	Dice d1;
//	Dice d2;
//
//
//
//	// Pushing in vector.
//	vector<Country*> p1Countries;
//	// Player 2 countries.
//	vector<Country*> p2Countries;
//
//
//	vector<Country>* countries = Player::gameMap->getListCountryPtr();
//	//vector<Country> countryvecor = Player::gameMap->getListCountry();
//	for (vector<Country>::iterator it = countries->begin(); it != countries->end(); it++) {
//		if (it->getNamePlayer() == name1)
//			p1Countries.push_back(&(*it));
//		else if (it->getNamePlayer() == name2)
//			p2Countries.push_back(&(*it));
//	}
//	
//
//	// Player hands.
//	Hand h1;
//	Hand h2;
//
//	// Player armies.
//	int army1 = 10;
//	int army2 = 5;
//
//	// The number of times a player has exchanged cards.
//	int exchange1 = 3;
//	int exchange2 = 5;
//
//	// Creating the players.
//	Player p(name1, p1Countries, d1, h1, army1, exchange1);
//	Player p2(name2, p2Countries, d2, h2, army2, exchange2);
//	
//	Hand* p1Hand = p.getPlayerHandPtr();
//
//	for (int i = 0; i < 6; i++) {
//		Player::gameDeck->draw(*p1Hand);
//	}
//
//	p.reinforce();
//	p.attack();
//	p.fortify();
//}


//void methodDriver2() {
//	setup();
//	// Creating player names.
//	string name1 = GameBoard::_listPlayer->at(0).getPlayerName();
//	string name2 = GameBoard::_listPlayer->at(1).getPlayerName();
//	string name3 = GameBoard::_listPlayer->at(2).getPlayerName();
//
//	// Player dice.
//	Dice d1;
//	Dice d2;
//	Dice d3;
//
//	// Pushing in vector.
//	vector<Country*> p1Countries;
//	// Player 2 countries.
//	vector<Country*> p2Countries;
//	vector<Country*> p3Countries;
//
//	vector<Country>* countries = Player::gameMap->getListCountryPtr();
//	vector<Country> countryvecor = Player::gameMap->getListCountry();
//	for (vector<Country>::iterator it = countries->begin(); it != countries->end(); it++) {
//		if (it->getNamePlayer() == name1)
//			p1Countries.push_back(&(*it));
//		else if (it->getNamePlayer() == name2)
//			p2Countries.push_back(&(*it));
//	}
//
//	for (vector<Country>::iterator it = countries->begin(); it != countries->end(); it++) {
//
//		p3Countries.push_back(&(*it));
//	}
//
//	// Player hands.
//	Hand h1;
//	Hand h2;
//
//	// Player armies.
//	int army1 = 10;
//	int army2 = 5;
//
//	// The number of times a player has exchanged cards.
//	int exchange1 = 3;
//	int exchange2 = 5;
//
//	// Creating the players.
//	Player p(name1, p1Countries, d1, h1, army1, exchange1);
//	Player p2(name2, p2Countries, d2, h2, army2, exchange2);
//	Player p3(name3, p3Countries, d1, h1, army1, exchange1);	//comment this line if you want to loop the game.
//	Hand* p1Hand = p.getPlayerHandPtr();
//
//	for (int i = 0; i < 6; i++) {
//		Player::gameDeck->draw(*p1Hand);
//	}
//
//
//	vector<Player*> players;
//	players.push_back(&p);
//	players.push_back(&p2);
//	players.push_back(&p3);//comment this line if you want to loop the game.
//	//GameLoop::executeLoop(players, countryvecor);
//
//
//	GameLoop::executeLoop(players, countryvecor);
//}


int main() {

	//Adapter Driver
	//adapterMain();

	//Create the gameboard object from user input
	GameBoard gameboard = GameEngine::initiateGame();

	//Create the game engine that stores the gameboard object that is shared between all players
	//Create the engine object in the main ensures that the gameboard object will exist throughout the program duration
	GameEngine engine = GameEngine::GameEngine(gameboard);


	Map* map= GameEngine::gameboard->getMapPtr();
	StaticsView* a = new StaticsView(map);

	
	//cout << "installing view" << endl;
	//Main game loop 
	engine.runLoop();





	////gameBoard object with all the required attributes
	//GameEngine::mainPart1();

	//cout << "-------------------------------------------------\n" <<
	//	"                     Game Start                \n" <<
	//	"-------------------------------------------------\n\n";

	//cout << "Testing country assignment:" << endl;
	//GameEngine::mainPart2();
	//
	//cout << endl;

	//methodDriver2();
	//methodDriver();
}
