#include "Map.h"

Country::Country() {
	_id = new int(0);
	_numArmies = new int(0);
	_continentID = new int(0);
	_namePlayer = new string("Undefined");
	_nameCountry = new string("Undefined");
}

Country::Country(int id, int numArmies, int continentID, string namePlayer, string nameCountry) :
	_id(new int(id)), _numArmies(new int(numArmies)), _continentID(new int(continentID)), _namePlayer(new string(namePlayer)), _nameCountry(new string(nameCountry)) {
}

Country::Country(const Country& country) {
	_id = new int(*country._id);
	_numArmies = new int(*country._numArmies);
	_continentID = new int(*country._continentID);
	_namePlayer = new string(*country._namePlayer);
	_nameCountry = new string(*country._nameCountry);
}

Country::~Country() {
	delete _id;
	delete _numArmies;
	delete _continentID;
	delete _namePlayer;
	delete _nameCountry;
}

int Country::getContinentID() const {
	return *_continentID;
}

void Country::setContinentID(const int continentID) {
	_continentID = new int(continentID);
}

int Country::getId() const {
	return *_id;
}

void Country::setId(int id) {
	_id = &id;
}
//c
int Country::getNumArmies() const {


	return *_numArmies;
}

void Country::setNumArmies(int numArmies) {
	if(_numArmies != nullptr)
		delete _numArmies;

	this->_numArmies = new int(numArmies);
}

void Country::addArmies(const int num)
{
	_numArmies = new int((*_numArmies) += num);
}

string Country::getNamePlayer() const {
	return *_namePlayer;
}

void Country::setNamePlayer(string namePlayer) {
	if (_namePlayer != nullptr)
		delete _namePlayer;

	this->_namePlayer = new string(namePlayer);
}

string Country::getNameCountry() const {
	return *_nameCountry;
}

void Country::setNameCountry(string nameCountry) {
	this->_nameCountry = &nameCountry;
}

Continent::Continent() :
	_listCountry(new vector<Country>), _name(new string("Undefined")), _numOfArmies(0) {
}

Continent::Continent(vector<Country>& listCountry, string name, int numOfArmies) :
	_listCountry(new vector<Country>(listCountry)), _name(new string(name)), _numOfArmies(new int(numOfArmies)) {
}

Continent::Continent(const Continent& continent) {
	_listCountry = new vector<Country>(*continent._listCountry);
	_name = new string(*continent._name);
	_numOfArmies = new int(*continent._numOfArmies);
}

Continent::~Continent() {
	delete _listCountry;
	delete _name;
}

vector<Country> Continent::getListCountry() const {
	return *_listCountry;
}

vector<Country>* Continent::getListCountryPtr() {
	return _listCountry;
}

string Continent::getName() const {
	return *_name;
}

void Continent::setName(string name) {
	_name = new string(name);
}

int Continent::getNumOfArmies() const {
	return *_numOfArmies;
}

void Continent::addCountry(Country& country) {
	(*_listCountry).push_back(country);
}

Map::Map(vector<Country> listCountry, vector<Continent> listContinent, vector<vector<int>> borderMatrix) :
	_listCountry(new vector<Country>(listCountry)), _listContinent(new vector<Continent>(listContinent)) {
	bool validMap = true;
	//Verification on the validity of the map
	for (int i = 0; i < borderMatrix.size(); i++) {
		for (int j = 0; j < borderMatrix[i].size(); j++) {
			if (borderMatrix[i][j] == 1 && borderMatrix[j][i] != 1) {
				validMap = false;
			}
		}
	}
	if (!validMap) {
		_borderMatrix = new vector<vector<int>>;
	}
	else {
		_borderMatrix = new vector<vector<int>>(borderMatrix);
	}
}

Map::Map() : _listCountry(new vector<Country>), _listContinent(new vector<Continent>), _borderMatrix(new vector<vector<int>>) {
}

Map::Map(const Map& m) :
	_borderMatrix(new vector<vector<int>>(*m._borderMatrix)), _listCountry(new vector<Country>(*m._listCountry)), _listContinent(new vector<Continent>(*m._listContinent)) {
}

Map::~Map() {
	delete _borderMatrix;
	delete _listCountry;
	delete _listContinent;
}

void Map::operator=(const Map& m) {
	_borderMatrix = new vector<vector<int>>(*m._borderMatrix);
	_listCountry = new vector<Country>(*m._listCountry);
	_listContinent = new vector<Continent>(*m._listContinent);
}

void Map::displayNeigbors(Country country) {
	for (int i = 0; i < (*_borderMatrix).size(); i++) {
		if ((*_borderMatrix)[country.getId() - 1][i] == 1) {
			std::cout << (*_listCountry)[i].getNameCountry() << "\n";
		}
	}
}

void Map::displayCountries(Continent continent) {
	for (int i = 0; i < continent.getListCountry().size(); i++) {
		cout << continent.getListCountry()[i].getNameCountry() << "\n";
	}
}

vector<vector<int>> Map::getBorderMatrix() {
	return *_borderMatrix;
}

vector<Country> Map::getListCountry() {
	return *_listCountry;
}

vector<Country>* Map::getListCountryPtr() {
	return _listCountry;
}

vector<Continent> Map::getListContinent() {
	return *_listContinent;
}

vector<Continent>* Map::getListContinentPtr() {
	return _listContinent;
}

int Map::getNumberOfCountry() const {
	return size(*_listCountry);
}

bool Map::isValid() const {
	return _borderMatrix->size() == 0 ? false : true;
}

vector<Country> Map::getNeighbours(Country country) {
	vector<Country> neighbours;

	for (int i = 0; i < (*_borderMatrix).size(); i++) {
		if ((*_borderMatrix)[country.getId() - 1][i] == 1) {
			neighbours.push_back(_listCountry->at(i));	//i think the problem is coming from here potentially.
		}
	}

	return neighbours;
}

void Map::changed() {
	notify();
}