#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;


class Dice {
	
public:
	Dice();
	Dice(int* total, vector<int> current, vector<int> numberoccured);
	Dice(const Dice& dice);
	~Dice();
	int* total;
	vector<int>* current;
	vector<int>* numberoccured;
	int Random_roll();
	double percentage(int num);
	vector<int> play(int n);
	int gettotal() const { return *total; }
	vector<int> getcurrent() const { return *current; }
	void settotal(int a) { total = new int(a); }
};

int Dicemain();
