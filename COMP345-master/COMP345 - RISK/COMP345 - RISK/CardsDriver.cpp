/*
Driver creates a deck of cards with an equal share of infantry, artillery and cavalry. Creates a
hand object that is filled by drawing cards from the deck, and that return the right number of
armies when the exchange() method is called, depending on what cards are in the hand.
*/

#include <stdio.h>
#include <string>
#include "Cards.h"
#include "Player.h"
#include <iostream>
using namespace std;


void cardsMain() {

	cout << "\n---------------------------" << endl;
	cout << "Starting Cards Driver" << endl;
	cout << "---------------------------" << endl;


	Player p; // Player to test hand.

	int nbTimesPlayer = 2;
	int nbArmies = 20;
	Deck deckObj1(50);
	Hand* handTry = p.getPlayerHandPtr();

	// Number of each card in deck.
	cout << "Composition of the deck: " << endl;
	cout << "The number of infantry: " << deckObj1.getNbI() << endl;
	cout << "The number of artillery: " << deckObj1.getNbA() << endl;
	cout << "The number of cavalry: " << deckObj1.getNbC() << endl;


	// for loop to add 10 cards to the hand of the player
	for (int i = 0; i < 10; i++) {
		deckObj1.draw(*handTry);
	}

	// Player's hand.
	vector<Card>* hand = handTry->getHandPtr();
	cout << "Player hand before exchange consists of: ";
	for (vector<Card>::iterator it = hand->begin(); it != hand->end(); it++) {
		Card c = *it;
		int n = *c.type;
		cout << n << " ";
	}

	cout << endl;

	// creating cards to pass as the cards chosen by the player in the exchange method
	Card card1P{};
	Card card2P{};
	Card card3P{};
	int typeI = 1;
	int typeA = 2;
	int typeC = 3;
	
	// finding a card with type 'i' in the hand of the player and assigning that type to a card 
	// Card will be passed down in the parameters of the exchange method 
	for (vector<Card>::iterator it = hand->begin(); it != hand->end(); ++it) {
		Card c1 = *it;
		if (*c1.type == typeI) {
			card1P.type = new int(*c1.type);
			break;
		}
	}
	// finding a card with type 'a' in the hand of the player and assigning that type to a card 
	// Card will be passed down in the parameters of the exchange method 
	for (vector<Card>::iterator it = hand->begin(); it != hand->end(); ++it) {
		//deckObj1->getCardI = it;
		Card c1 = *it;
		if (*c1.type == typeA) {
			card2P.type = new int(*c1.type);
			break;
		}
	}
	// finding a card with type 'c' in the hand of the player and assigning that type to a card 
	// Card will be passed down in the parameters of the exchange method 
	for (vector<Card>::iterator it = hand->begin(); it != hand->end(); ++it) {
		//deckObj1->getCardI = it;
		Card c1 = *it;
		if (*c1.type == typeC) {
			card3P.type = new int(*c1.type);
			break;
		}
	}
	
	// creating an integer pointer that stores the number of armies returned by the exchange method
	int nbArmiesExch = handTry->exchange(card1P, card2P, card3P, nbTimesPlayer, deckObj1);

	// Player's hand after exchanging.
	cout << "Player hand after exchange consists of: ";
	for (vector<Card>::iterator it = hand->begin(); it != hand->end(); it++) {
		Card c = *it;
		int n = *c.type;
		cout << n << " ";
	}

	cout << endl;

	/* printing out information to test the driver */
	cout << "The number of armies obtained after an exchange if it's the second exchange is: " << nbArmiesExch << endl;

	cout << "Done!" << endl;

}