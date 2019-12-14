#include "GameEngine.h"

//vector<Player>* GameBoard::_listPlayer = nullptr;
GameBoard* GameEngine::gameboard = nullptr;

GameBoard::GameBoard()
{
	_map = new Map();
	_deckOfCards = new Deck(0);
	_listPlayer = new vector<Player>();
}

GameBoard::GameBoard(Map& map, Deck& deck, vector<Player>& listPlayer) :
	_map(new Map(map)), _deckOfCards(new Deck(deck)), _listPlayer(new vector<Player>(listPlayer)) 
{
}

GameBoard::GameBoard(const GameBoard& gm) {
	_map = new Map(*gm._map);
	_listPlayer = new vector<Player>(*gm._listPlayer);
	_deckOfCards = new Deck(*gm._deckOfCards);
}

void GameBoard::operator=(const GameBoard& gm) {
	_map = new Map(*gm._map);
	_listPlayer = new vector<Player>(*gm._listPlayer);
	_deckOfCards = new Deck(*gm._deckOfCards);
}

Map GameBoard::getMap() const {
	return *_map;
}

vector<Player> GameBoard::getListPlayer() const {
	return *_listPlayer;
}

Deck GameBoard::getDeckOfCard() const {
	return *_deckOfCards;
}

vector<Player>* GameBoard::getListPlayerPtr() const
{
	return _listPlayer;
}

Map* GameBoard::getMapPtr() const
{
	return _map;
}

Deck* GameBoard::getDeckOfCardPtr() const
{
	return _deckOfCards;
}

void GameBoard::setListPlayer(vector<Player>& listPlayer)
{
	_listPlayer = new vector<Player>(listPlayer);
}

Map GameEngine::mapSelector() {
	// I have made to choice to made the list of map static, we have to manually update the vector of map filename when we add a map,
	// this is certainly not perfect, but it does the job.
	vector<string> nameMap = { "canada.map", "europass.map", "germany.map","invalid.map" };
	
	//With the adapter
	//vector<string> nameMap = { "canada.map", "europass.map", "germany.map","invalid.map", "Africa.map", "Atlantis.map" };

	cout << "-------------------------------------------------\n" <<
			"                  Map Selection                  \n" <<
			"     Please select the map you want to play      \n" <<
			"-------------------------------------------------\n\n";

	for (int i = 0; i < nameMap.size(); i++) {
		cout << i << " - " << nameMap[i] << "\n";
	}

	int choice;
	Map map;
	bool valid = false;
	while (!valid) {
		valid = true;
		cout << "\nPlease enter the number associated with you favorite map: ";
		cin >> choice;

		if (choice < 0 || choice >= nameMap.size()) {
			valid = false;
			cout << "This number is not a possible choice, please try again";
		}
		MapLoader maploader("map/" + nameMap[choice]);
		map = maploader.parseMap();
		if (!map.isValid()) {
			cout << "Invalid Map";
			valid = false;
		}
	}

	return map;


}

vector<Player> GameEngine::numberOfPlayer() {
	cout << "\n\n-------------------------------------------------\n" <<
		"                 Player Selection                \n" <<
		"      Now let's select the number of player      \n" <<
		"                that wants to play!              \n" <<
		"-------------------------------------------------\n\n";

	int choice;
	bool valid = false;
	while (!valid) {
		valid = true;
		cout << "\nPlease enter the number of player that wants to play: ";
		cin >> choice;

		if (choice < 0 || choice > 6) {
			valid = false;
			cout << "This number is not a possible choice. Please try again.";
		}
	}

	cout << endl;

	vector<Player> listPlayer(choice);

	for (int i = 0; i < choice; i++) {
		string name;
		cout << "Please enter the name of player " << i + 1 << ": ";
		cin >> name;
		int typeOfPlayer;
		do {
			cout << "Are they (1) human, (2) aggressive CPU, (3) benevolent CPU?:,(5) cheater CPU?: ";
			cin >> typeOfPlayer;
			if (typeOfPlayer < 1 || typeOfPlayer > 5)
				cout << "Invalid number, please try again." << endl;
		} while (typeOfPlayer < 1 || typeOfPlayer > 5);
		
		Strategy* playerStrat = nullptr;

		switch (typeOfPlayer) {
		case 1:
			playerStrat = new PlayerStrategy();
			break;
		case 2:
			playerStrat = new AggressiveStrategy();
			break;
		case 3:
			playerStrat = new BenevolentStrategy();
			break;
		case 5:
			playerStrat = new CheaterStrategy();


		}

		//Create to call to constructor
		vector<Country*> list;
		Player p(name, list, Dice(), Hand(), 0, 0, playerStrat);
		listPlayer[i] = p;
		// Creating a concrete phase observer for each player created
		ConcretePhaseObserver* phaseObs1 = new ConcretePhaseObserver(&listPlayer[i]);
	}

	return listPlayer;
}

GameBoard GameEngine::initiateGame() {
	cout << "-------------------------------------------------\n" <<
			"               Welcome to the game of            \n" <<
			"                        RISK                     \n" <<
			"-------------------------------------------------\n\n\n";


	//Ask player to select the map
	Map map = GameEngine::mapSelector();
	if (!map.isValid()) {
		cout << "Invalid Map selected!\n";
	}
	//Create the list of player with desired attributes
	vector<Player> listPlayer = GameEngine::numberOfPlayer();

	//Create the deck of card
	Deck deck(map.getNumberOfCountry());

	//Create a game board

	GameBoard gm(map, deck, listPlayer);

	return gm;
}

// Driver for demo
//void GameEngine::mainPart1() {
//	//Initiate the gameboard
//	GameBoard gm = GameEngine::initiateGame();
//
//	//Get the list of player
//	vector<Player> lp = gameboard.g;
//
//	//Display the players info
//	cout << "\nThere are " << lp.size() << " players in the game : \n";
//	for (int i = 0; i < lp.size(); i++) {
//		cout << lp[i].getPlayerName() << "\n";
//	}
//	//Display num of card in deck
//
//	cout << "\nAnd there are " << gm.getDeckOfCard().getDeck().size() << " cards in the deck" << endl << endl;
//
//
//
//}


GameLoop::GameLoop() : _listCountry(new vector<Country>), listPlayer(new vector<Player>) {
}
GameLoop::GameLoop(vector<Player>& alistPlayer, vector<Country>& alistCountry) :
	listPlayer(new vector<Player>(alistPlayer)), _listCountry(new vector<Country>(alistCountry)) {}
GameLoop::GameLoop(const GameLoop& gameloop) {
	listPlayer =  new vector<Player>(*gameloop.listPlayer);
	_listCountry = new vector<Country>(*gameloop._listCountry);
}
GameLoop::~GameLoop() {
	delete listPlayer;
	delete _listCountry;
}
vector<Player> GameLoop::getlistPlayer() const {
	return *listPlayer;

}
vector<Country>GameLoop::getlistCountry() const {
	return *_listCountry;
}

void GameLoop::executeLoop(vector<Player*>& players, vector<Country>& Country) {	//maybe i should use continent and get list of all country
	bool continuing = true;
	string winner = "null";
	do {
		for (size_t i = 0; i < players.size(); i++) {
			if (players[i]->getPlayerCountries().size() == Country.size()) {
				winner = players[i]->getPlayerName();
				continuing = false;
				break;
			}
			players[i]->reinforce();
			players[i]->attack();
			players[i]->fortify();
		}
	} while (continuing);

	cout << "The winner is " << winner << "! Please don't be a tyrant!" << endl;

}

// Part2

GameEngine::GameEngine(GameBoard& gm) {
	//Set the pointer to the gameboard
	gameboard = &gm;

	// Changes the order of player in the player vector of the gameboard
	orderPlayers();	

	//Assign Countries to player
	assignCountries();

	// printing out eahc player's countries to check that every country belongs to one and only one player
	for (int i = 0; i < gameboard->getListPlayerPtr()->size(); i++) {
		cout << "\n" << gameboard->getListPlayerPtr()->at(i).getPlayerName() << "'s countries:" << endl;
		int counter = 0;
		for (int j = 0; j < gameboard->getListPlayerPtr()->at(i).getPlayerCountriesPtr()->size(); j++) {
			cout << counter << ". " << gameboard->getListPlayerPtr()->at(i).getPlayerCountriesPtr()->at(j)->getNameCountry() << endl;
			counter++;
		}
	}

	placeArmies();
	// printing out the number of armies in each player's countries and the total number of armies for each player
	for (int i = 0; i < gameboard->getListPlayerPtr()->size(); i++) {
		int nbArmPlayer = 0;
		cout << "\n" << gameboard->getListPlayerPtr()->at(i).getPlayerName() << "'s armies:" << endl;
		for (int j = 0; j < gameboard->getListPlayerPtr()->at(i).getPlayerCountriesPtr()->size(); j++) {
			cout << gameboard->getListPlayerPtr()->at(i).getPlayerCountriesPtr()->at(j)->getNameCountry() 
				 << " has " << gameboard->getListPlayerPtr()->at(i).getPlayerCountriesPtr()->at(j)->getNumArmies() << endl;
			nbArmPlayer += gameboard->getListPlayerPtr()->at(i).getPlayerCountriesPtr()->at(j)->getNumArmies();
		}
		cout << "This player has " << nbArmPlayer << " armies.\n" << endl;
	}

	//gameboard

}


// Function which orders the players randomly. Takes into consideration the number of players.
void GameEngine::orderPlayers() {

	int nbPlayers = gameboard->getListPlayer().size();
	// creating a vector pointer in the players will be added
	vector<Player> orderedPlay;
	/*
	a place is the index of a player in the original vector of players passed to the constructor
	takes a random number as the first place ad every other place is chosen randomly in a loop to verify that it's not already assigned to a previous place
	the players are pushed by the new random order into the orderedPlay vector
	*/
	if (nbPlayers == 2) {
		int plc1 = rand() % 2;
		orderedPlay.push_back(gameboard->getListPlayer().at(plc1));
		int plc2 = 2 - plc1 - 1;
		orderedPlay.push_back(gameboard->getListPlayer().at((plc2)));
	}
	else if (nbPlayers == 3) {
		int plc1 = rand() % 3;
		int plc2 = plc1;
		while (plc2 == plc1) {
			plc2 = rand() % 3;
		}
		int plc3 = 3 - plc1 - plc2;
		orderedPlay.push_back(gameboard->getListPlayer().at(plc1));
		orderedPlay.push_back(gameboard->getListPlayer().at(plc2));
		orderedPlay.push_back(gameboard->getListPlayer().at(plc3));
	}
	else if (nbPlayers == 4) {
		int plc1 = rand() % 4;
		int plc2 = plc1;
		int plc3 = plc1;
		int plc4 = plc1;
		while (plc2 == plc1) {
			plc2 = rand() % 4;
		}
		while (plc3 == plc2 || plc3 == plc1) {
			plc3 = rand() % 4;
		}
		plc4 = 6 - plc1 - plc2 - plc3;
		orderedPlay.push_back(gameboard->getListPlayer().at(plc1));
		orderedPlay.push_back(gameboard->getListPlayer().at(plc2));
		orderedPlay.push_back(gameboard->getListPlayer().at(plc3));
		orderedPlay.push_back(gameboard->getListPlayer().at(plc4));
	}
	else if (nbPlayers == 5) {
		int plc1 = rand() % 5;
		int plc2 = plc1;
		int plc3 = plc1;
		int plc4 = plc1;
		int plc5 = plc1;
		while (plc2 == plc1) {
			plc2 = rand() % 5;
		}
		while (plc3 == plc2 || plc3 == plc1) {
			plc3 = rand() % 5;
		}
		while (plc4 == plc2 || plc4 == plc1 || plc4 == plc3) {
			plc4 = rand() % 5;
		}
		plc5 = 10 - plc1 - plc2 - plc3 - plc4;
		orderedPlay.push_back(gameboard->getListPlayer().at(plc1));
		orderedPlay.push_back(gameboard->getListPlayer().at(plc2));
		orderedPlay.push_back(gameboard->getListPlayer().at(plc3));
		orderedPlay.push_back(gameboard->getListPlayer().at(plc4));
		orderedPlay.push_back(gameboard->getListPlayer().at(plc5));
	}
	else if (nbPlayers == 6) {
		int plc1 = rand() % 6;
		int plc2 = plc1;
		int plc3 = plc1;
		int plc4 = plc1;
		int plc5 = plc1;
		int plc6 = plc1;
		while (plc2 == plc1) {
			plc2 = rand() % 6;
		}
		while (plc3 == plc2 || plc3 == plc1) {
			plc3 = rand() % 6;
		}
		while (plc4 == plc2 || plc4 == plc1 || plc4 == plc3) {
			plc4 = rand() % 6;
		}
		while (plc5 == plc2 || plc5 == plc1 || plc5 == plc3 || plc5 == plc4) {
			plc5 = rand() % 6;
		}
		plc6 = 15 - plc1 - plc2 - plc3 - plc4 - plc5;
		orderedPlay.push_back(gameboard->getListPlayer().at(plc1));
		orderedPlay.push_back(gameboard->getListPlayer().at(plc2));
		orderedPlay.push_back(gameboard->getListPlayer().at(plc3));
		orderedPlay.push_back(gameboard->getListPlayer().at(plc4));
		orderedPlay.push_back(gameboard->getListPlayer().at(plc5));
		orderedPlay.push_back(gameboard->getListPlayer().at(plc6));
	}

	 gameboard->setListPlayer(orderedPlay);
}

// Function to assign Countries to each Player
void GameEngine::assignCountries() {
	int nbInGame = gameboard->getListPlayer().size();
	int nbCountries = gameboard->getMap().getNumberOfCountry();
	// vector of boolean that keeps up with if a country has been assigned so a country will not be assigned more than once
	vector<bool> assigned(nbCountries, false);

	int nbP = 0;
	while (nbP < assigned.size()) {
		// playNow is the index of the player in the vector
		int playNow = nbP % (nbInGame);
		// a random index of the country list is chosen
		int place = rand() % nbCountries;
		
		// adding the random country to a player's country vector by creating a temporary vector which is the same as the player's country vector
		// pushing the new random country to that temporary vector and finally setting the player's country vector to the temp vector
		if (assigned.at(place) == false) {

			//This one liner add the country
			gameboard->getListPlayerPtr()->at(playNow).getPlayerCountriesPtr()->push_back(&gameboard->getMapPtr()->getListCountryPtr()->at(place));
			gameboard->getMapPtr()->getListCountryPtr()->at(place).setNamePlayer(gameboard->getListPlayerPtr()->at(playNow).getPlayerName());
			assigned.at(place) = true;
			nbP++;
		}
	}
}

// Function to assign armies to whichever country the player chooses
void GameEngine::placeArmies() {
	int nbPlayersInGame = gameboard->getListPlayerPtr()->size();
	int maxNumberOfArmy = 0;

	switch(nbPlayersInGame) {
		case 2 :
			maxNumberOfArmy = 80;
			break;
		case 3:
			maxNumberOfArmy = 105;
			break;
		case 4:
			maxNumberOfArmy = 120;
			break;
		case 5:
			maxNumberOfArmy = 125;
			break;
		case 6:
			maxNumberOfArmy = 120;
			break;
	}
	int totalNumberOfArmy = 0;
	bool found = false;
	int cntrNumber;
	int playerId = 0;
	while (totalNumberOfArmy != maxNumberOfArmy) {
		cout << "On what country do you want to place 5 armies? Please enter the number:" << endl;
		cout << gameboard->getListPlayerPtr()->at(playerId).getPlayerName() << ": ";
		cin >> cntrNumber;
		// adding an army to that country's number of armies
		if (cntrNumber < (gameboard->getListPlayerPtr()->at(playerId).getPlayerCountries().size())) {
			gameboard->getListPlayerPtr()->at(playerId).getPlayerCountries().at(cntrNumber)->addArmies(5);
			found = true;
			totalNumberOfArmy += 5;
		}
		// printing a message if the country chosedn is not part of a player's countries
		if (!found) {
			cout << "You do not have this country! Please try again!" << endl;
		}
		playerId = (playerId + 1) % nbPlayersInGame;
	}
}

void GameEngine::runLoop()
{
		bool continuing = true;
		string winner = "null";
		do {
			for (int i = 0; i < gameboard->getListPlayerPtr()->size(); i++) {
				if (gameboard->getListPlayerPtr()->at(i).getPlayerCountries().size() == gameboard->getMapPtr()->getListCountryPtr()->size()) {
					winner = gameboard->getListPlayerPtr()->at(i).getPlayerName();
					continuing = false;
					break;
				}
				gameboard->getListPlayerPtr()->at(i).reinforce();
				gameboard->getListPlayerPtr()->at(i).attack();
				gameboard->getListPlayerPtr()->at(i).fortify();
			}
		} while (continuing);

		cout << "The winner is " << winner << "! Please don't be a tyrant!" << endl;
}

// Destructor
GameEngine :: ~GameEngine() {
	delete gameboard;
}

//void GameEngine::mainPart2() {
//
//	// Creating countries.
//	Country country1(1, 0, 0, "Player1", "country1");
//	Country country2(2, 0, 0, "Player1", "country2");
//	Country country3(3, 0, 1, "Player1", "country3");
//	Country country4(4, 0, 1, "Player1", "country4");
//	Country country5(5, 0, 1, "Player2", "country5");
//	Country country6(6, 0, 1, "Player2", "country6");
//
//	vector<Country> countryListAll{ country1, country2, country3, country4, country5, country6 };
//	vector<Country> countryList1{ country1, country2 };
//	vector<Country> countryList2{ country3, country4, country5, country6 };
//	Continent continent1(countryList1, "continent1", 4);
//	Continent continent2(countryList2, "continent2", 6);
//	vector<Continent> listContinent{ continent1, continent2 };
//
//	// Creating the matrix.
//	vector<int> row1{ 0,1,0,0,0,0 };
//	vector<int> row2{ 1,0,1,0,0,1 };
//	vector<int> row3{ 0,1,0,1,0,0 };
//	vector<int> row4{ 0,0,1,0,0,0 };
//	vector<int> row5{ 0,0,0,0,0,1 };
//	vector<int> row6{ 0,1,0,0,1,0 };
//
//	// Full map.
//	vector<vector<int>> borderMatrix{ row1, row2, row3, row4, row5, row6 };
//
//	Map map(countryListAll, listContinent, borderMatrix);
//
//	//return new Map(map);
//
//	// Creating player names.
//	string name1 = "Player1";
//	string name2 = "Player2";
//
//	// Player dice.
//	Dice d1;
//	Dice d2;
//
//	// Pushing in vector.
//	vector<Country*> p1Countries;
//	// Player 2 countries.
//	vector<Country*> p2Countries;
//
//	vector<Country>* countries = Player::gameMap->getListCountryPtr();
//
//	for (vector<Country>::iterator it = countries->begin(); it != countries->end(); it++) {
//		if (it->getNamePlayer() == name1)
//			p1Countries.push_back(&(*it));
//		else if (it->getNamePlayer() == name2)
//			p2Countries.push_back(&(*it));
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
//
////	Hand* p1Hand = p.getPlayerHandPtr();
//
//	// creating the original vector of players which isnt ordered yet
//	vector<Player*> playersMain2;
//	playersMain2.push_back(new Player(p));
//	playersMain2.push_back(new Player(p2));
//
//	// calling the constructor 
//	GameEngine gameEngPart2(playersMain2);
//	gameEngPart2.setPlayersInGame(&playersMain2);
//	// creating the map
//	Map* mapGameEngPt2 = new Map(map);
//	gameEngPart2.assigningCountries(*mapGameEngPt2);
//
//	// printing out eahc player's countries to check that every country belongs to one and only one player
//	for (auto p : playersMain2) {
//		cout << p->getPlayerName() << "'s countries:" << endl;
//		int counter = 0;
//		for (auto c : p->getPlayerCountries()) {
//			string nameCountryC = c->getNameCountry();
//			cout << counter << ". " << nameCountryC << endl;
//			counter++;
//		}		
//	}
//
//	// printing out the number of armies in each player's countries and the total number of armies for each player
//	gameEngPart2.placeArmies();
//	for (auto p : playersMain2) {
//		int nbArmPlayer = 0;
//		cout << p->getPlayerName() << "'s armies:" << endl;
//		for (auto c : p->getPlayerCountries()) {
//			cout << c->getNameCountry() << " has " << c->getNumArmies() << " armies" << endl;
//			nbArmPlayer += c->getNumArmies();
//		}
//		cout << "This player has " << nbArmPlayer << " armies." << endl;
//	}
//
//	// calling the destructor
//	delete mapGameEngPt2;
//}
