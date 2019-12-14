# COMP345
Risk Game
Made by: Cerine Madi(40097761), Nathan Alix-Vignola(40086963), Janghyuk Boo(40005573) and Weiliang Xie(40100475).

# Warning (FIXED): 
The map selection may not work by simply importing files.
Otherwise they work as intended on local machines.
This will further be demonstrated during the demo.
For the purposes of the demo, 3 players need to be entered.
This can be changed later on, but must stay for the test drivers.

## Introduction
This first assignment was separated into multiple parts.
Cerine Madi took care of the "Cards" part.
Jangyuk Boo took care of the "Dice" part.
Nathan Alix-Vignola took care of the "Map" and "MapLoader" part.
Weiliang Xie took care of the "Player" part.

## Assignment 3
The game logic is now implemented.
Different design patterns have now been implemented to add functionality and versatility to the game.
Three different strategies were implemented: Human player strategy, aggressive computer player stratetgy, and benevolent computer player strategy. The two computer players make choices independent of any direct input and follow the same rules and logic as the human player.
Two different observer patterns were implemented, one keeping track of each player's phases and displaying the relevant information, the other keeping track of the going-ons of the game map.
Finally, an adapter for a different kind of map file is implemented, allowing more versatility to the type of maps that can be used.

## Assignment 2
This part of the assignment started implementing game logic.
Players can now attack(), fortify(), and reinforce().
Players can now choose a map file from a list of map files.
The game phase can now start with player selection as well as country assignment.
Each player now gets a turn to do all necessary actions in a round-robin fashion.
A win condition has been specified. If a player owns all countries on the map, the are declared the winner.

## Cards
The "Cards" part consists of 3 files called "Cards.h", "Cards.cpp", and "CardsDriver.cpp".
There are 2 classes (Deck and Hand) as well as a struct (Card).
There are 3 card types (Infantry,  Artillery, Cavalry) represented by integer values (1, 2, 3).
The Deck class has an attribute deck, a vector of Cards which holds all the cards for the game (equivalent to the number of countries).
It has a draw() method, allowing Player Hand objects to draw from it, thus decreasing the size of the deck and increasing the size of a Hand.
The Hand class has an attribute hand, a vector of Cards which holds all the cards a player would own.
It has an exchange() method which allows 3 cards (of the same type or of all different types) to be exchanged for armies, decreasing the size of a Hand.

## Dice
The "Dice" part consists of 3 files called "Dice.h", "Dice.cpp", "DiceDriver.cpp".
There is a class Dice which keeps count of the number of times a certain value (1-6) is rolled, every time it is rolled.
Rolling this Dice produces a random value each time.
It has been rolled 2000 times to show a percentage value that is pretty much equivalent between all values rolled.

## Map
The "Map" part consists of 3 files called "Map.h", "Map.cpp", and "MapDriver.cpp".
It has classes Country, Continent, and Map.
Multiple methods and attributes allows one to know how many armies on that country and who it belongs too.
A continent has a vector of Countries which resides on it.
A map is the total vector of all Continents and Countries and takes into account each neighbour and their connection (via a border matrix).

## MapLoader
The "MapLoader" part consists of 3 files called "MapLoader.h", "MapLoader.cpp", and "MapLoaderDriver.cpp".
It reads input files and parses the into maps that can be used for the game.
Can now differentiate between a valid and invalid map.
Further details are in the files themselves.

## Player
The "Player" part consists of 3 files called "Player.h", "Player.cpp", "PlayerDriver.cpp".
These Player objects have a Hand and 1 to 3 Dice objects in their possesion.
Reinforce() now allows players to exchange cards to gain armies to place on select countries that they own.
Attack() now allows players to attack neighbouring enemy countries and conquer them or lose armies in the process.
Fortify() now allows players to move armies from one country that they own to another.

## GameEngine
The "GameEngine" part takes care of the background game setup as well as loop.
From the map selection, the player selection, the pre-game setup as well as the actual game loop, this implements that actual metagame logic.
Different classes were implemented to ensure that all of it works.
