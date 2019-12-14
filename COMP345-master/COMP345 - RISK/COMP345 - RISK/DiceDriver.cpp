#include <iostream>
#include <string>
#include "Dice.h"
#include "Player.h"
using namespace std;


int Dicemain() {

	cout << "\n---------------------------" << endl;
	cout << "Starting Dice Driver:" << endl;
	cout << "---------------------------" << endl;

	// Player to test dice.
	Player p;
	Dice d;

	p.setPlayerDice(d);

	for (int i = 0; i < 10; i++) {
		cout << "how many? (1-3)" << endl;
		int num;
		cin >> num; 
		if (num > 3) {
			cout << "please re-enter the value within 1-3" << endl;
		}
		else {
			cout << endl;
			d.play(num);
		}
	}


	// Testing the algorithm for the probabilities.
	Dice dice;
	cout << "Run the algorithm 2000 times? (y/n): ";
	string input;
	cin >> input;
	if (input == "y") {
		for (int j = 0; j < 2000; j++) {
			dice.play(3);
		}

		// Results.
		cout << endl;
		cout << "Dice number 1 occured " << dice.percentage(1) << " %"<< endl;
		cout << "Dice number 2 occured " << dice.percentage(2) << " %" << endl;
		cout << "Dice number 3 occured " << dice.percentage(3) << " %" << endl;
		cout << "Dice number 4 occured " << dice.percentage(4) << " %" << endl;
		cout << "Dice number 5 occured " << dice.percentage(5) << " %" << endl;
		cout << "Dice number 6 occured " << dice.percentage(6) << " %" << endl;
	}
	else {
		cout << "Skipping." << endl;
	}

	cout << "Done!" << endl;

	return 0;
}