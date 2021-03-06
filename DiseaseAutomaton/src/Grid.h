/*
 * Grid.h
 *
 *  Jakub Suchecki
 *  B00045505
 *  year 2014
 */

#ifndef GRID_H_
#define GRID_H_

#include <vector>
#include <iostream>
#include <fstream>
#include "Cell.h"
#include "HelperFunctions.h"
#include <time.h>
using std::string;
using std::cout;
using std::ios;
using std::cerr;
using std::endl;

using std::ofstream;
using std::ifstream;

class Grid {
public:
	Grid();
	Grid(int, int, int,int,float,float,float,float);
	virtual ~Grid();
	std::vector <Cell> grid;
	unsigned int row;
	unsigned int col;
	int infectionTime;
	float infectionProbability;
	float deathRate;//for each person who was ill for the infectionTime
	float naturalDeathRate;
	float birthRate;//per cell
	unsigned long population;
	unsigned long infected;
	unsigned long recovered;
	unsigned long susceptible;
	int peopleInACell;
	void updateStats();
	void printStats();
	void resetStats();//
	void printGrid();
	void printGridStat(char);
	void printGridInfected();
	void printGridSusceptible();
	void printGridRecovered();
	void printGridPopulation();
	void printAllPeopleStates();
	void printPeopleStatesInACell(int, int);
	void infectionPoint (int,int,int);
	void computeGrid ();
	void fillPeopleVector();
	void saveGridToFile (string);
	bool loadGridFromFile (string);



};

#endif /* GRID_H_ */
