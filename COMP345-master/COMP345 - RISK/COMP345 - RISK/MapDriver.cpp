#include "Map.h"

int mapMain() {
	cout << "---------------------------" << endl;
	cout << "Starting Map Driver: " << endl;
	cout << "---------------------------" << endl;

	// Creating the countries.
	string s1("dsadsad");
	string s2("Fdsfsd");
	Country c1;
	Country c2(2, 9, 0, s1, s2);

	// Vectors for the country.
	vector<Country> v1;
	v1.push_back(c1);
	v1.push_back(c2);

	// Creating continents.
	Continent con1;
	Continent con2(v1, "C2", 4);

	std::cout << "Two Players: " << c1.getNamePlayer() << " and " << c2.getNamePlayer() << "\nContinent name: " << con2.getName() << endl;

	// Creating countries.
	Country country1(1, 200, 0, "john", "country1");
	Country country2(2, 300, 0, "john", "country2");
	Country country3(3, 20, 1, "john", "country3");
	Country country4(4, 600, 1, "john", "country4");
	Country country5(5, 700, 1, "john", "country5");
	Country country6(6, 100, 1, "john", "country6");

	vector<Country> countryListAll{ country1, country2, country3, country4, country5, country6 };
	vector<Country> countryList1{ country1, country2 };
	vector<Country> countryList2{ country3, country4, country5, country6 };
	Continent continent1(countryList1, "continent1", 4);
	Continent continent2(countryList2, "continent2", 6);
	vector<Continent> listContinent{ continent1, continent2 };

	// country1 neighbors: country2
	// country2 neighbors: country1, country3, country 6
	// country3 neighbors: country2, country4
	// country4 neighbors: country3
	// country5 neighbors: country6
	// country6 neighbors: country2, country 5

	// Creating the matrix.
	vector<int> row1{ 0,1,0,0,0,0 };
	vector<int> row2{ 1,0,1,0,0,1 };
	vector<int> row3{ 0,1,0,1,0,0 };
	vector<int> row4{ 0,0,1,0,0,0 };
	vector<int> row5{ 0,0,0,0,0,1 };
	vector<int> row6{ 0,1,0,0,1,0 };

	// Full map.
	vector<vector<int>> borderMatrix{ row1, row2, row3, row4, row5, row6 };

	// Creating the map object.
	Map map(countryListAll, listContinent, borderMatrix);

	std::cout << "Map:\n";
	std::cout << "Continent 1: " << endl;
	map.displayCountries(continent1);
	std::cout << "\nNeighbour of Country 2: " << endl;
	map.displayNeigbors(country2);
	std::cout << "\nEnd\n";
	return 0;
}