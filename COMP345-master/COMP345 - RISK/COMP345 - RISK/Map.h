#pragma once
#include <iostream>
#include <vector>
class StatisticSubject;
#include "GameObservers.h"
using namespace std;


class Country {
private:
	//0-based index
	int* _id;
	int* _numArmies;
	//0-based index
	int* _continentID;
	string* _namePlayer;
	string* _nameCountry;
public:
	Country();
	Country(int id, int numArmies, int continentID, string namePlayer, string nameCountry);
	Country(const Country& country);
	~Country();

	int getContinentID() const;
	void setContinentID(const int continentID);

	int getId() const;
	void setId(const int id);

	int getNumArmies() const;
	void setNumArmies(const int numArmies);
	void addArmies(const int num);

	string getNamePlayer() const;
	void setNamePlayer(const string namePlayer);

	string getNameCountry() const;
	void setNameCountry(const string nameCountry);
};

class Continent {
private:
	vector<Country>* _listCountry;
	string* _name;
	int* _numOfArmies;

public:
	Continent();
	Continent(vector<Country>& listCountry, string name, int numOfArmies);
	Continent(const Continent& continent);
	~Continent();

	vector<Country> getListCountry() const;
	vector<Country>* getListCountryPtr();

	int getNumOfArmies() const;

	string getName() const;
	void setName(string name);

	void addCountry(Country& country);

};

class Map: public StatisticSubject {
private:
	//Pointers to borderMatrix array, listCountry array and listContinent array
	vector<vector<int>>* _borderMatrix;
	vector<Country>* _listCountry;
	vector<Continent>* _listContinent;
public:
	//Map Constructor and destructor
	Map(vector<Country> listCountry, vector<Continent> listContinent, vector<vector<int>> borderMatrix); //Return nullptr if map is invalid
	Map();
	Map(const Map& m);
	~Map();

	void operator=(const Map& m);

	void displayNeigbors(Country country);
	void displayCountries(Continent continent);
	vector<vector<int>> getBorderMatrix();
	vector<Country> getListCountry();
	vector<Country>* getListCountryPtr();
	vector<Continent> getListContinent();
	vector<Continent>* getListContinentPtr();
	vector<Country> getNeighbours(Country country);
	void changed();
	int getNumberOfCountry() const;
	bool isValid() const;
};

int mapMain();

