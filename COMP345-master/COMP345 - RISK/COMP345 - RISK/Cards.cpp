#include "Cards.h"
#include <iostream>

using namespace std;

Card::Card() {
	type = new int(0);
}

Card::Card(int num) {
	type = new int(num);
}

Card::Card(const Card& c) {
	type = new int(*(c.type));
}

/* Construtor */
Deck::Deck(int numOfCountries) {
	nbCountries = new int(numOfCountries);
	int nbI1 = 0; // integer for the number of infantry
	int nbA1 = 0; // integr for the number of artillery
	int nbC1 = 0; // integer for the number of cavalry
	deck = new vector<Card>;
	drawn = new Card;

	if ((*nbCountries % 3) == 1) {
		// assigns correct numbers to the 3 types of cards if the number of countries is not a multiple of 3 and there is a remainder of 1
		nbI1 = (*nbCountries / 3) + 1;
		nbA1 = *nbCountries / 3;
		nbC1 = *nbCountries / 3;
	}

	if ((*nbCountries % 3) == 2) {
		// assigns correct numbers to the 3 types of cards if the number of countries is not a multiple of 3 and there is a remainder of 2
		nbI1 = (*nbCountries / 3) + 1;
		nbA1 = (*nbCountries / 3) + 1;
		nbC1 = *nbCountries / 3;
	}

	if ((*nbCountries % 3) == 0) {
		// assigns correct numbers to the 3 types of cards if the number of countries i a multiple of 3
		nbI1 = *nbCountries / 3;
		nbA1 = *nbCountries / 3;
		nbC1 = *nbCountries / 3;
	}

	// assigning the integer to the integer pointer
	nbI = new int(nbI1);
	nbA = new int(nbA1);
	nbC = new int(nbC1);

	// creating integers that represent each type of card and assigning them to new cards pointers
	int typeI = 1;
	cardI = new Card();
	cardI->type = new int(typeI);
	int typeA = 2;
	cardA = new Card();
	cardA->type = new int(typeA);
	int typeC = 3;
	cardC = new Card();
	cardC->type = new int(typeC);

	// for loop to randomly add the different types of card to the deck
	for (int i = 0, j = 0, k = 0; (i + j + k) < *nbCountries;) {
		Card c1(0);
		Card c2(0);
		Card c3(0);

		int r1 = rand() % 3;
		switch (r1) {
		case 0:
			if (i == (nbI1)) {
				break;
			}
			i++;
			c1.type = new int(typeI);
			deck->push_back(c1); // adding a card of type 1
			break;
		case 1:
			if (j == (nbA1)) {
				break;
			}
			j++;
			c2.type = new int(typeA);
			deck->push_back(c2); // adding a card of type 2
			break;
		case 2:
			if (k == (nbC1)) {
				break;
			}
			k++;
			c3.type = new int(typeC);
			deck->push_back(c3); // adding a card of type 3
			break;
		}
	}
}

/* Destructor */
Deck::~Deck() {
	deck->clear();
	delete deck;
	delete nbCountries;
	delete nbA;
	delete nbI;
	delete nbC;
	delete cardI;
	delete cardA;
	delete cardC;
	delete drawn;
}

//Copy constructor
Deck::Deck(const Deck& d) {
	deck = new vector<Card>(*d.deck);
	nbCountries = new int(*d.nbCountries);
	nbA = new int(*d.nbA);
	nbI = new int(*d.nbI);
	nbC = new int(*d.nbC);
	cardI = new Card(*d.cardI);
	cardA = new Card(*d.cardA);
	cardC = new Card(*d.cardC);
	drawn = new Card(*d.drawn);
}

//Assignment operator
void Deck::operator=(const Deck& d) {
	deck = new vector<Card>(*d.deck);

	nbCountries = new int(*d.nbCountries);
	nbA = new int(*d.nbA);
	nbI = new int(*d.nbI);
	nbC = new int(*d.nbC);
	cardI = new Card(*d.cardI);
	cardA = new Card(*d.cardA);
	cardC = new Card(*d.cardC);
	drawn = new Card(*d.drawn);
}

/* Draw method */
Card Deck::draw(Hand& hand1) {
	Card drawn{ 0 };
	int type = *(deck->back().type);
	drawn.type = new int(type); // the card drawn is the last card in the deck
	hand1.addCardToHand(drawn); // added the card drawn to the player's hand
	//delete deck->back();
	deck->pop_back(); // removig the card drawn from the deck
	return drawn;
}

// Getters
vector<Card> Deck::getDeck() const {
	return *deck;
}
vector<Card>* Deck::getDeckPtr() const {
	return deck;
}
int Deck::getNbCountries() const {
	return *nbCountries;
}
int* Deck::getNbAPtr() const {
	return nbA;
}
int* Deck::getNbIPtr() const {
	return nbI;
}
int* Deck::getNbCPtr() const {
	return nbC;
}
int Deck::getNbA() const {
	return *nbA;
}
int Deck::getNbI() const {
	return *nbI;
}
int Deck::getNbC() const {
	return *nbC;
}
Card Deck::getCardI() const {
	return *cardI;
}
Card Deck::getCardA() const {
	return *cardA;
}
Card Deck::getCardC() const {
	return *cardC;
}

// Setter
void Deck::setNbCountries(int newNbCountries) {
	nbCountries = new int(newNbCountries);
}


/* Constructor */
Hand::Hand() {
	hand = new vector<Card>; // intializing the vector which represents the hand of cards
}

Hand::Hand(const Hand& h) {
	hand = new vector<Card>(*h.hand);
}

void Hand::operator=(const Hand& h) {
	hand = new vector<Card>(*h.hand);
}

/* exchange method */
int Hand::exchange(Card card1, Card card2, Card card3, int times, Deck& d) {

	vector<Card>* handP1 = getHandPtr(); // hand pointer to the player's hand
	vector<Card>* deck1 = d.getDeckPtr(); // deck pointer to the deck

	// creating integers that represent each type of card and assigning them to integers 
	int typeI = 1;
	int typeA = 2;
	int typeC = 3;

	// Case in which it's 3 cards of the same type
	if (*(card1.type) == *(card2.type) && *(card2.type) == *(card3.type)) {
		int typeCard = *(card1.type);

		// looping through the vector to find and erase a card that has the same type as the one the player entered
		// 3 identical loops because the same card
		for (vector<Card>::iterator it = handP1->begin(); it != handP1->end(); ++it) {
			Card c = *it;
			if (*(c.type) == typeCard) {
				handP1->erase(it);
				break;
			}
		}
		for (vector<Card>::iterator it = handP1->begin(); it != handP1->end(); ++it) {
			Card c = *it;
			if (*(c.type) == typeCard) {
				handP1->erase(it);
				break;
			}
		}
		for (vector<Card>::iterator it = handP1->begin(); it != handP1->end(); ++it) {
			Card c = *it;
			if (*(c.type) == typeCard) {
				handP1->erase(it);
				break;
			}
		}
		// finding the number of armies to return considering how many times a player calls this function
		int nbArmies = 5 * times;
		times++;
		// adding the cards removed from the hand back to the deck
		Card putBack{ 0 };
		int newType = *card1.type;
		putBack.type = new int(newType);

		cout << "Putting back " << *putBack.type << endl;

		deck1->push_back(putBack);
		deck1->push_back(putBack);
		deck1->push_back(putBack);

		return nbArmies;
	}
	// Case in which it's 3 cards of the different types
	else if (*(card1.type) != *(card2.type) && *(card2.type) != *(card3.type) && *(card1.type) != *(card3.type)) {
		// looping through the vector to find and erase a card that has the same type as the one the player entered
		// 3 similar loops because the 3 different cards
		for (vector<Card>::iterator it = handP1->begin(); it != handP1->end(); ++it) {
			Card c = *it;
			if (*c.type == typeI) {
				handP1->erase(it);
				break;
			}
		}
		for (vector<Card>::iterator it = handP1->begin(); it != handP1->end(); ++it) {
			Card c = *it;
			if (*c.type == typeA) {
				handP1->erase(it);
				break;
			}
		}
		for (vector<Card>::iterator it = handP1->begin(); it != handP1->end(); ++it) {
			Card c = *it;
			if (*c.type == typeC) {
				handP1->erase(it);
				break;
			}
		}

		// finding the number of armies to return considering how many times a player calls this function
		int nbArmies = 5 * times;
		times++;
		// adding the cards removed from the hand back to the deck

		int type1 = *d.getCardI().type;
		Card card1I{ 0 };
		card1I.type = new int(type1);
		deck1->push_back(card1I);

		int type2 = *d.getCardA().type;
		Card card2A{ 0 };
		card2A.type = new int(type2);
		deck1->push_back(card2A);

		int type3 = *d.getCardC().type;
		Card card3C{ 0 };
		card3C.type = new int(type3);
		deck1->push_back(card3C);

		return nbArmies;
	}
	// Case in which it's the combination of cards chosen is not valid for an exchange
	else {
		// -1 is error
		int errorNb = -1;
		return errorNb;
	}
}

/* Destructor */
Hand :: ~Hand() {
	hand->clear();
	delete hand;
}

vector<Card> Hand::getHand() const {
	return *hand;
}

vector<Card>* Hand::getHandPtr() const {
	return hand;
}

void Hand::addCardToHand(Card c) {
	hand->push_back(c);
}