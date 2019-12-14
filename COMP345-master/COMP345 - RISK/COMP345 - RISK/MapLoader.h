#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <sstream>
#include <map>
#include <algorithm>
#include "Map.h"

using namespace std;

class MapLoader
{
private:
	string* _fileName;
	
	// Get the information needed from the file.
	vector<string> parseRows(string s);
	vector<vector<int>> parseBorderMatrix(string s);
	vector<Country> parseCountryList(string s);
	vector<Continent> parseContinentList(string s, vector<Country>& countryList);
	

public:
	MapLoader();
	MapLoader(string fileName);
	MapLoader(MapLoader& mapL);
	~MapLoader();

	Map parseMap();
};

// Adaptee interface (What was used before)
class NewMapLoader {
private:
	//Parsing methods for new file
	vector<string> parseContinentsName(string s);
	vector<string> parseRows(string s);
	vector<vector<int>> parseBorderMatrix(string s, vector<Country>& countryList ) ;
	vector<Country> parseCountryList(string s, vector<string> continentList);
	vector<Continent> parseContinentList(vector<string> continentName, vector<Country>& countryList);
public:
	Map parseMapNew(string fileName);
};


// MapLoaderAdapter
// As the tutor told us, I made another class for the new map format. In the case we had other map format, we can just
// add new classes. Then in the apdapter, I added a boolean attributes that is set during construction that tells which class
// to use when parsiong the map. The when the parse method is called, the appropriate parseMap method is called.If more than 
// 2 file format had to be parsed, a struct could be used instead of a boolean.
class MapLoaderAdapter : public NewMapLoader, public MapLoader {
private:
	string* _fileName;
	bool* _old;
public:
	MapLoaderAdapter(string filename);
	MapLoaderAdapter(MapLoaderAdapter& mapL);
	~MapLoaderAdapter();

	Map parse();


};

int mapLoaderMain();
void adapterMain();

