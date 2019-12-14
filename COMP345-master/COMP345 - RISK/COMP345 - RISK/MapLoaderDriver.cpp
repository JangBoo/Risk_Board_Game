#include "MapLoader.h"
#include <iostream>

int mapLoaderMain()
{
	std::cout << "\n---------------------------" << endl;
	std::cout << "MapLoader Driver Start: " << endl;
	std::cout << "---------------------------" << endl;

	MapLoader mapload("map/canada.map");
	Map map;
	map = mapload.parseMap();
    std::cout << "Finished!\n";

	return 0;
}

void adapterMain()
{
	//Create two adapter object, one with a file with the old format and one with the new forma
	MapLoaderAdapter adapterOld("map/canada.map");
	MapLoaderAdapter adapterNew("map/Africa.map");

	//Create 2 maps using the adapter
	Map oldMap = adapterOld.parse();
	Map newMap = adapterNew.parse();

	//Printing list country in each map to prove that is exist
	cout << "Country of old map: \n";
	for (int i = 0; i < oldMap.getListCountry().size(); i++) {
		cout << oldMap.getListCountry()[i].getNameCountry() << "\n";
	}
	cout << "\n\n";
	cout << "Country of new map: \n";
	for (int i = 0; i < newMap.getListCountry().size(); i++) {
		cout << newMap.getListCountry()[i].getNameCountry() << "\n";
	}


}

