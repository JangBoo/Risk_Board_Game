#include <iostream>
#include <random>
#include <vector>
#include "Dice.h"

using namespace std;

Dice::Dice() {
	total = new int(0);
	current = new vector<int>();
	numberoccured= new vector<int>(6);
}

Dice::Dice(int* total, vector<int> current, vector<int> numberoccured) {
	this->total = total;
	this->current = new vector<int>(current);
	this->numberoccured = new vector<int>(numberoccured);

}

Dice::Dice(const Dice& dice)
{
	total = new int(*dice.total);
	current = new vector<int>(*dice.current);
	numberoccured = new vector<int>(*dice.numberoccured);
}

Dice::~Dice() {
	delete total;
	total = nullptr;
	delete current;
	current = nullptr;
	delete numberoccured;
	numberoccured = nullptr;
}
int Dice::Random_roll()
{
	int randomNum = (rand() % 6) + 1;
	(*total)++;
	numberoccured->push_back(randomNum - 1); // if it was vector, without this-->, i get pointer to object error , why?
	return randomNum;
}


double Dice::percentage(int num) {		//percentage of each number.
	return ((double)numberoccured->at(num - 1) / *total)*100;

}

vector<int> Dice::play(int n)	// 
{
	//ask player how many dice are being rolledled and get number/ keep it in container..

	// initialize it again here

	current->clear();

	for (int i=0; i <n; i++) 
	{	int val = Random_roll();
		current->push_back(val);			//is it sorted? no so sort it.
	}
	
	sort(current->begin(), current->end());

	cout << "[ ";

	for (vector<int>::iterator it = current->begin(); it != current->end(); ++it) {
		cout << *it << " ";
	}

	cout << "]" << endl;

	return *current;
}
