#include "GameObservers.h"
#include "Map.h"
#include "Player.h"
#include "GameEngine.h";
#include <string>

StatisticObserver::~StatisticObserver() {
}
StatisticObserver::StatisticObserver() {
}

StatisticSubject::StatisticSubject() {
	_observers = new list<StatisticObserver*>;
}
StatisticSubject::~StatisticSubject() {
	delete _observers;
}
void StatisticSubject::attach(StatisticObserver* o) {
	_observers->push_back(o);
}
void StatisticSubject::detach(StatisticObserver* o) {
	_observers->remove(o);
}
void StatisticSubject::notify() {
	list<StatisticObserver*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->update();
}

StaticsView::StaticsView() {

}

StaticsView::StaticsView(Map* map) {
	_subject = map;
	_subject->attach(this);

}

StaticsView::~StaticsView() {
	_subject->detach(this);

}

void StaticsView::update() {
	display();
}
void viewtable() {}
void StaticsView::display() {
	
	vector<Player>* playerlist = GameEngine::gameboard->getListPlayerPtr();
	
	Map* map  = _subject;
	int size =map->getListCountry().size();
	vector<Country> a = map->getListCountry();
	switch (playerlist->size()) {
	case 1:
		for (int j = 0; j < playerlist->size(); j++) {

			double percent = (playerlist->at(j).getPlayerCountries().size() / (double)size) * 100;
			cout << "Player " << playerlist->at(j).getPlayerName() << " has " << playerlist->at(j).getPlayerCountries().size() << " countries. They own " << percent << "% of the map!" << endl;
		}
		cout << "The winner is " << playerlist->at(0).getPlayerName() << " congrats! (Please don't be a tyrant)!" << endl;		
		system("pause");
		break;
	default:
		//cout << "size of plaeyrlist" << playerlist->size() << endl;
		for (int j = 0; j < playerlist->size(); j++) {

			double percent = (playerlist->at(j).getPlayerCountries().size() / (double)size) * 100;
			cout << "Player " << playerlist->at(j).getPlayerName() << " has " << playerlist->at(j).getPlayerCountries().size() << " countries. They own " << percent << "% of the map!"<< endl;
		}	
	}

	cout << endl;
}


// Constructor
PhaseObserver:: PhaseObserver() {
}
//Destructor
PhaseObserver::~PhaseObserver() {
}

//Constructor
PhaseSubject::PhaseSubject() {
	_phaseObservers = new vector<PhaseObserver*>;
}
//Destructor
PhaseSubject ::~PhaseSubject() {
}

// Detaching a phase observer (deleting it from the list)
void PhaseSubject::phaseDetach(PhaseObserver* Po) {
	for (int i = 0; i < (_phaseObservers->size()); i++) {
		if (_phaseObservers->at(i) == Po) {
			_phaseObservers->erase(_phaseObservers->begin() + i);
			break;
		}
	}
}

// attaching a phase observer (adding it to the list)
void PhaseSubject::phaseAttach(PhaseObserver* Po) {
	_phaseObservers->push_back(Po);
}
// notify method for attack which will call the update attack for a phase observer
void PhaseSubject::notifyAttack(string country, string countryA, string nameA, int result, int roArmies, string roCountry, int attArmies, string name) {
	for (int i = 0; i < (_phaseObservers->size()); i++) {
		_phaseObservers->at(i)->updateAttack(country, countryA, nameA, result, roArmies, roCountry, attArmies, name);
	}

}
// notify method for fortify which will call the update fortify for a phase observer
void PhaseSubject::notifyFortify(string country, string fCountry, int cArmies, int fArmies, string name) {
	for (int i = 0; i < (_phaseObservers->size()); i++) {
		_phaseObservers->at(i)->updateFortify(country, fCountry, cArmies, fArmies, name);
	}
}
// notify method for reinforce which will call the update reinforce for a phase observer
void PhaseSubject::notifyReinforce(int nbArmies, string country, string name) {
	for (int i = 0; i < _phaseObservers->size(); i++) {
		_phaseObservers->at(i)->updateReinforce(nbArmies, country, name);
	}
}

 // Constructor
ConcretePhaseObserver::ConcretePhaseObserver() {
	_phaseSubject = nullptr;
}
// Parametrized constructor
ConcretePhaseObserver::ConcretePhaseObserver(Player* p) {
	_phaseSubject = p;
	_phaseSubject->phaseAttach(this);
}
// Destructor
ConcretePhaseObserver::~ConcretePhaseObserver() {
	_phaseSubject->phaseDetach(this);
}

// update attack method which override update attack from Phase Observer and calls the display method of the concrete phase observer
void ConcretePhaseObserver::updateAttack(string cntr, string cntrA, string nmA, int res, int roArm, string roCntr, int attArm, string name) {
	displayAttack(cntr, cntrA, nmA, res, roArm, roCntr, attArm, name);
}
// update fortify method which override update fortify from Phase Observer and calls the display method of the concrete phase observer
void ConcretePhaseObserver::updateFortify(string cntr, string fCntr, int cArm, int fArm, string name) {
	displayFortify(cntr, fCntr, cArm, fArm, name);
}
// update reinforce method which override update reinforce from Phase Observer and calls the display method of the concrete phase observer
void ConcretePhaseObserver::updateReinforce(int nbA, string cntr, string name) {
	displayReinforce(nbA, cntr, name);
}
// method to display what happened during the attack phase with relevent information
void ConcretePhaseObserver::displayAttack(string c, string cA, string nA, int r, int roA, string roC, int attA, string name) {
	cout << endl << name << ": Attack phase" << endl << name << " attacked " << cA << ", which belongs to " << nA << ", from " << c << endl;
	if (r == 0) {
		cout << "After the attack " << name << " has " << roA << " on " << roC << "." << endl;
		cout << nA << " has " << attA << " on " << cA << "." << endl << endl;
	}
	else {
		cout << "After the attack " << name << " has " << roA << " on " << roC << "." << endl;
		cout << name << " conquered " << cA << "." << endl << endl;
	}

}
// method to display what happened during the fortification phase with relevent information
void ConcretePhaseObserver::displayFortify(string c, string fC, int cA, int fA, string name) {
	cout << endl << name << ": Fortification phase" << endl << name << " chose armies from " << c << " and fortified  " << fC << "." << endl;
	cout << c << " now has " << cA << " armies." << endl;
	cout << fC << " now has " << fA << " armies." << endl << endl;
}
// method to display what happened during the reinforcement phase with relevent information
void ConcretePhaseObserver::displayReinforce(int nA, string c, string name) {
	cout << endl << name << ": Reinforcement phase" << endl << name << " put " << nA << " armies on the country " << c << "." << endl << endl;
}



