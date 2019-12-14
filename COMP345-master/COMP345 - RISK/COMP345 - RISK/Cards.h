#pragma once
#include <vector>
#include "Map.h"


using namespace std;

class Hand;

// Structure to create an object with a data member but with no methods
struct Card {
	// data member is an integer that represents the type of the card which will be infantry(1), artillery(2) or cavalry(3).
	// The data member is named type
	int* type;
	Card();
	Card(int type);
	Card(const Card& c);
};

class Deck {
private:
	// a vector pointer is created to store the cards of the deck
	vector<Card>* deck;
	// number of countries to create the right number of cards
	int* nbCountries;
	int* nbA; // integer pointer which stores the right number of cards of type artillery
	int* nbI; // integer pointer which stores the right number of cards of type infantry
	int* nbC; // integer pointer which stores the right number of cards of type cavalry
	Card* cardI; // Card pointer which stores the Card which has 1 as a type
	Card* cardA; // Card pointer which stores the Card which has 2 as a type
	Card* cardC; // Card pointer which stores the Card which has 3 as a type
	Card* drawn; // Card pointer which stores the Card which has as a type the same type as the card drawn in the draw() method


public:
	// constructor
	Deck(int numOfCountries);
	// destructor
	~Deck();

	Deck(const Deck& d);

	void operator=(const Deck& d);
	// draw function
	Card draw(Hand& hand1);

	// Getters
	vector<Card> getDeck() const;
	vector<Card>* getDeckPtr() const;
	int getNbCountries() const;
	int* getNbAPtr() const;
	int* getNbIPtr() const;
	int* getNbCPtr() const;
	int getNbA() const;
	int getNbI() const;
	int getNbC() const;
	Card getCardI() const;
	Card getCardA() const;
	Card getCardC() const;

	// Setter
	void setNbCountries(int newNbCountries);
};

class Hand {

private:
	// a vector is created to store the cards of a player's hand
	vector<Card>* hand;

public:
	// constructor
	Hand();
	//Hand(const Hand& hand);
	// destructor
	~Hand();

	Hand(const Hand& h);

	void operator=(const Hand& h);

	// exchange method that returns a number of armies
	int exchange(Card card1, Card card2, Card card3, int times, Deck& d);

	// Getters
	vector<Card> getHand() const;
	vector<Card>* getHandPtr() const;

	void addCardToHand(Card c);
};

// main method for Cards Driver
void cardsMain();