#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Map.h"

using namespace std;

class Country;
class Map;
class Player;
class Strategy;
class PlayerStrategy;
class AggressiveStrategy;
class BenevolentStrategy;


class Strategy {
public:
	virtual bool proceed(string phase) = 0;
	virtual int chooseOwnCountry(vector<Country*>* countries) = 0;
	virtual bool continuePhase(string phase, bool canContinue) = 0;
	virtual int chooseCountry(vector<Country> countries) = 0;
	virtual int getNumOfDice(Country& c, string type);
	virtual int numOfArmiesToMove(Country& c) = 0;
	virtual int executeReinforce(vector<Country*>* countries, int a) = 0;
	virtual void placeit(Country* cntry, int* numArmy) = 0;
	int getarmynum() { return armynum; };
	string getname() { return name; };

protected:
	int armynum;
	string name;
};

class PlayerStrategy : public Strategy {
public:
	virtual bool proceed(string phase) override;
	virtual int chooseOwnCountry(vector<Country*>* countries) override;
	virtual bool continuePhase(string phase, bool canContinue) override;
	virtual int chooseCountry(vector<Country> countries) override;
	virtual int getNumOfDice(Country& c, string type) override;
	virtual int numOfArmiesToMove(Country& c) override;
	virtual int executeReinforce(vector<Country*>* countries, int a) override;
	virtual void placeit(Country* cntry, int* numArmy) override;
};

class AggressiveStrategy : public Strategy {
public:
	string type = "aggressive";
//	void reinforce2(int* numArmyPtr);
	virtual int executeReinforce(vector<Country*>* countries, int a) override;
	virtual void placeit(Country* cntry, int* numArmy);
	virtual bool proceed(string phase) override;
	virtual int getNumOfDice(Country& c, string type) override;
	virtual int chooseOwnCountry(vector<Country*>* countries) override;
	virtual bool continuePhase(string phase, bool canContinue) override;
	virtual int chooseCountry(vector<Country> countries) override;
	virtual int numOfArmiesToMove(Country& c) override;
};

class BenevolentStrategy : public Strategy {
public:
	virtual int executeReinforce(vector<Country*>* countries, int a) override;
	virtual void placeit(Country* cntry, int* numArmy);
	virtual bool proceed(string phase) override;
	virtual int chooseOwnCountry(vector<Country*>* countries) override;
	virtual bool continuePhase(string phase, bool canContinue) override;
	virtual int chooseCountry(vector<Country> countries) override;
	virtual int numOfArmiesToMove(Country& c) override;
};

class RandomStrategy : public Strategy {
public:
	virtual int executeReinforce(vector<Country*>* countries, int a) override;
	virtual void placeit(Country* cntry, int* numArmy);
	virtual bool proceed(string phase) override;
	virtual int chooseOwnCountry(vector<Country*>* countries) override;
	virtual bool continuePhase(string phase, bool canContinue) override;
	virtual int chooseCountry(vector<Country> countries) override;
	virtual int numOfArmiesToMove(Country& c) override;
};

class CheaterStrategy : public Strategy {
	virtual int executeReinforce(vector<Country*>* countries, int a) override;
	virtual bool proceed(string phase) override;
	virtual void placeit(Country* cntry, int* numArmy) override;
	virtual int chooseOwnCountry(vector<Country*>* countries) override;
	virtual bool continuePhase(string phase, bool canContinue) override;
	virtual int chooseCountry(vector<Country> countries) override;
	virtual int numOfArmiesToMove(Country& c) override;
};

