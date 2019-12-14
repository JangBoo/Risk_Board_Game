#include "MapLoader.h"

vector<string> MapLoader::parseRows(string s) {
	vector<string> rows;

	//Define the regex for the split
	const regex separator{ "\\n" };
	//Create the iterator object from the stringg
	sregex_token_iterator iterator(s.begin(), s.end(), separator, -1);
	sregex_token_iterator end;

	//Loop on the iterator and remove the commented and empty row. Put each row in a vector
	while (iterator != end) {
		char y = ';';
		string row = (*iterator).str();
		if (row.length() == 0 || row[0] == ';') {
			++iterator;
			continue;
		}
		rows.push_back(*iterator);
		++iterator;
	}
	return rows;
}

//This parse the [Border] section in the map file and make a adjacency matrix out of it.
vector<vector<int>> MapLoader::parseBorderMatrix(string s) {

	vector<string> rows = parseRows(s);
	//Initialize a 2D vector array with the correct number of nodes.
	vector<vector<int>> matrix(size(rows), vector<int>(size(rows)));


	//Populate the matrix using the rows' information.
	for (int i = 0; i < size(rows); i++) {
		stringstream stream(rows[i]);
		int index, temp;
		stream >> index;
		while (stream >> temp) {
			matrix[index - 1][temp - 1] = 1;
		}

	}
	return matrix;
}

//Create the vector of country object out of the info in the map file
vector<Country> MapLoader::parseCountryList(string s) {
	vector<Country> listCountry;
	vector<string> rows = parseRows(s);
	//Get the info neccessary to create a country object from each row of the file
	for (int i = 0; i < size(rows); i++) {
		stringstream stream(rows[i]);
		int index, continentID;
		string name;
		stream >> index;
		stream >> name;
		stream >> continentID;
		Country country(index - 1, 0, continentID - 1, "Undefined", name);
		listCountry.push_back(country);
	}

	return listCountry;
}

//Create the vector of continent object out of the info in the map file
vector<Continent> MapLoader::parseContinentList(string s, vector<Country>& countryList) {
	vector<Continent> listContinent;
	vector<string> rows = parseRows(s);

	//Create the vector of continent 
	for (int i = 0; i < size(rows); i++) {
		stringstream stream(rows[i]);
		string name;
		stream >> name;

		//Insert en empty country list that we will fill later
		vector<Country> list;
		Continent continent(list, name, 4);
		listContinent.push_back(continent);
	}

	//Loop through all of the countries and add them to their appropriate continent
	for (int i = 0; i < size(countryList); i++) {
		//Get the continent id of each country and add them the to right continent country list
		listContinent[countryList[i].getContinentID()].addCountry(countryList[i]);
	}


	return listContinent;
}

MapLoader::MapLoader() : _fileName(new string("No file name")) {
}

MapLoader::MapLoader(string fileName) : _fileName(new string(fileName)) {
}

MapLoader::MapLoader(MapLoader& mapL) {
	_fileName = new string(*mapL._fileName);
}

MapLoader::~MapLoader() {
	delete _fileName;
}
Map MapLoader::parseMap() {
	//Create an input stream to the file and turn the file content into a string
	ifstream inputStream(*_fileName);
	string fileContent((istreambuf_iterator<char>(inputStream)), (istreambuf_iterator<char>()));

	vector<string> parts;

	//Define the regex for the split
	const regex separator{ "\\[\\w+\\]" };
	//Iterate through the fileContent string and split the string according to the regexp expression
	sregex_token_iterator iterator(fileContent.begin(), fileContent.end(), separator, -1);
	sregex_token_iterator end;

	while (iterator != end) {
		parts.push_back(*iterator);
		++iterator;
	}

	//Parse the different vectors needed for the creation of the map
	vector<vector<int>> borderMatrix = parseBorderMatrix(parts[4]);
	vector<Country> listCountry = parseCountryList(parts[3]);
	vector<Continent> listContinent = parseContinentList(parts[2], listCountry);

	Map mapGame(listCountry, listContinent, borderMatrix);


	return mapGame;



}

MapLoaderAdapter::MapLoaderAdapter(string filename) : _fileName(new string(filename))
{
	if (filename == "map/Africa.map" || filename == "map/Atlantis.map") {
		_old = new bool(false);
	}
	else {
		_old = new bool(true);
	}
}

MapLoaderAdapter::MapLoaderAdapter(MapLoaderAdapter& mapL)
{
	_fileName = new string(*mapL._fileName);
	_old = new bool(*mapL._old);
}

MapLoaderAdapter::~MapLoaderAdapter()
{
	delete _fileName;
	delete _old;
}

Map MapLoaderAdapter::parse()
{
	// If old is set to true, because i cannot change the old map loader implementation, I create a mapLoader object and
	// return the object that is produced by it. Else I return, the parseMap method of the new class. Like this as long as 
	// new classes have a public class method that takes a string as parameter, we can use it in our adapter. Like this all of
	// the parsing part is abstracted to the user and only a method is necessary to parse a map of many file format.
	if (*_old) {
		MapLoader maploader(*_fileName);
		return maploader.parseMap();
	}
	else {
		return parseMapNew(*_fileName);
	}
	// We could add other parse methods for other file format like this
	/*} else if (*fileformat == x) {
		return parseMapX(*_fileName);
    } else if (*fileformat == y) {
		return parseMapy(*_fileName);
    } else if (*fileformat == x) {
		return parseMapZ(*_fileName);
    }
	*/

}

vector<string> NewMapLoader::parseContinentsName(string s)
{
	vector<string> listContinentName;
	vector<string> rows = parseRows(s);

	//Create the vector of continent 
	for (int i = 0; i < size(rows); i++) {
		replace(rows[i].begin(), rows[i].end(), ' ', '%');
		replace(rows[i].begin(), rows[i].end(), '=', ' ');
		stringstream stream(rows[i]);
		string name;
		stream >> name;
		replace(name.begin(), name.end(), '%', ' ');
		listContinentName.push_back(name);
	}

	return listContinentName;
}

vector<string> NewMapLoader::parseRows(string s)
{
	vector<string> rows;

	//Define the regex for the split
	const regex separator{ "\\n" };
	//Create the iterator object from the stringg
	sregex_token_iterator iterator(s.begin(), s.end(), separator, -1);
	sregex_token_iterator end;

	//Loop on the iterator and remove the commented and empty row. Put each row in a vector
	while (iterator != end) {
		char y = ';';
		string row = (*iterator).str();
		if (row.length() == 0 || row[0] == ';') {
			++iterator;
			continue;
		}
		rows.push_back(*iterator);
		++iterator;
	}
	return rows;
}

vector<vector<int>> NewMapLoader::parseBorderMatrix(string s, vector<Country>& countryList)
{
	vector<string> rows = parseRows(s);
	vector<vector<int>> matrix(size(rows), vector<int>(size(rows)));
	
	//Map that maps a country name to its index
	std::map<string, int> mapCountry;
	for (int i = 0; i < countryList.size(); i++) {
		mapCountry[countryList[i].getNameCountry()] = i;
	}

	for (int i = 0; i < size(rows); i++) {
		replace(rows[i].begin(), rows[i].end(), ' ', '%');
		replace(rows[i].begin(), rows[i].end(), ',', ' ');
		stringstream stream(rows[i]);
		string blankString,name;
		int blankNum;
		//Remove non necessary string and int from the stream
		stream >> blankString;
		stream >> blankNum;
		stream >> blankNum;
		stream >> blankString;
		//Get all the neighbors of the country and set them into the matrix
		while (stream >> name) {
			replace(name.begin(), name.end(), '%', ' ');
			matrix[i][mapCountry[name]] = 1;
		}
	}
	return matrix;
}

vector<Country> NewMapLoader::parseCountryList(string s, vector<string> continentList)
{
	vector<Country> listCountry;
	vector<string> rows = parseRows(s);
	int index, continentID;
	string name, continentName;
	//Get the info neccessary to create a country object from each row of the file
	for (int i = 0; i < size(rows); i++) {
		replace(rows[i].begin(), rows[i].end(), ' ', '%');
		replace(rows[i].begin(), rows[i].end(), ',', ' ');
		stringstream stream(rows[i]);
		stream >> name;
		//To get past the coordinates
		stream >> index;
		stream >> index;
		stream >> continentName;
		replace(continentName.begin(), continentName.end(), '%', ' ');
		for (int i = 0; i < continentList.size(); i++) {
			if (continentName == continentList[i]) {
				continentID = i;
				break;
			}
		}

		replace(name.begin(), name.end(), '%', ' ');
		Country country(i, 0, continentID, "Undefined", name);
		listCountry.push_back(country);
	}

	return listCountry;
}

vector<Continent> NewMapLoader::parseContinentList(vector<string> continentName, vector<Country>& countryList)
{
	vector<Continent> listContinent;
	for (int i = 0; i < continentName.size(); i++) {
		vector<Country> listCountry;
		for (int j = 0; j < countryList.size(); j++) {
			if (countryList[j].getContinentID() == i) {
				listCountry.push_back(countryList[j]);
			}
		}
		listContinent.push_back(Continent(listCountry, continentName[i], 0));
	}
	return listContinent;
}

Map NewMapLoader::parseMapNew(string fileName)
{
	//Create an input stream to the file and turn the file content into a string
	ifstream inputStream(fileName);
	string fileContent((istreambuf_iterator<char>(inputStream)), (istreambuf_iterator<char>()));

	vector<string> parts;

	//Define the regex for the split
	const regex separator{ "\\[\\w+\\]" };
	//Iterate through the fileContent string and split the string according to the regexp expression
	sregex_token_iterator iterator(fileContent.begin(), fileContent.end(), separator, -1);
	sregex_token_iterator end;

	while (iterator != end) {
		parts.push_back(*iterator);
		++iterator;
	}

	//Parse the different vectors needed for the creation of the map
	vector<string> listNameContinent = parseContinentsName(parts[2]);
	vector<Country> listCountry = parseCountryList(parts[3], listNameContinent);
	vector<vector<int>> borderMatrix = parseBorderMatrix(parts[3], listCountry);
	vector<Continent> listContinent = parseContinentList(listNameContinent, listCountry);

	Map map(listCountry, listContinent, borderMatrix);


	return map;


}
