#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;
class Country;
class Map;
class Player;
class StatisticObserver;
class StaticsView;
class StatisticSubject;
class PhaseObserver;
class PhaseSubject;
class ConcretePhaseObserver;

// Observer pattern are implemented. 
// Map are used as a subject. 
// It reports the number of country player own and its percentage when finishing the attack phase. 
// Also when a player lose all its country, it removes player from the gameboard.
class StatisticObserver {
public:
	~StatisticObserver();
	virtual void update() = 0;
protected:
	StatisticObserver();
};

class StatisticSubject {
public:
	virtual void attach(StatisticObserver* o);
	virtual void detach(StatisticObserver* o);
	virtual void notify();
	StatisticSubject();
	~StatisticSubject();
	
private:
	list<StatisticObserver*>* _observers;
};



class StaticsView : public StatisticObserver {  
public:

	StaticsView(Map* ma);
	~StaticsView();
	void update();
	void display();
	
private:
	StaticsView();
	Map* _subject;
};

// Phase Observer
class PhaseObserver {
protected:
	// Default constructor
	PhaseObserver();
public:
	// Destructor
	~PhaseObserver();
	// virtual methods which are going to be overriden
	virtual void updateAttack(string cntr, string cntrA, string nmA, int res, int roArm, string roCntr, int attArm, string name) =0;
	virtual void updateFortify(string cntr, string fCntr, int cArm, int fArm, string name) =0;
	virtual void updateReinforce(int nbA, string cntr, string name) =0;
};

// Phase subject
class PhaseSubject {
public:
	// Default constructor, destructor
	PhaseSubject();
	~PhaseSubject();
	// virtual methods which are passed down to every player
	// methods have a declaration in the PhaseSubject class, they are not purely virtual
	virtual void phaseAttach(PhaseObserver* pO);
	virtual void phaseDetach(PhaseObserver* pO);
	virtual void notifyAttack(string country, string countryA, string nameA, int result, int roArmies, string roCountry, int attArmies, string name);
	virtual void notifyFortify(string country, string fCountry, int cArmies, int fArmies, string name);
	virtual void notifyReinforce(int nbArmies, string country, string name);
	
protected:
	// vector to add the phase observers for a phase subject
	vector<PhaseObserver*>* _phaseObservers;
};

//Concrete Phase Observer
class ConcretePhaseObserver : public PhaseObserver {
public:
	// Default constructor, parametrized constructor, destructor
	ConcretePhaseObserver();
	ConcretePhaseObserver(Player* p);
	~ConcretePhaseObserver();
	// Methods which override the virtual methods from PhaseObserver
	void updateAttack(string cntr, string cntrA, string nmA, int res, int roArm, string roCntr, int attArm, string name);
	void updateFortify(string cntr, string fCntr, int cArm, int fArm, string name);
	void updateReinforce(int nbA, string cntr, string name);
	// methods to display the phase
	void displayAttack(string c, string cA, string nA, int r, int roA, string roC, int attA, string name);
	void displayFortify(string c, string fC, int cA, int fA, string name);
	void displayReinforce(int nA, string c, string name);
private:
	// the player which belongs to this concrete phase observer
	Player* _phaseSubject;
};







