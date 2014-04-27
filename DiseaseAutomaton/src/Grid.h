/*
 * Grid.h
 *
 *  Created on: 11 Feb 2014
 *      Author: kuba
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
	Grid(int, int, int,int);
	virtual ~Grid();
	std::vector <Cell> grid;
	int row;
	int col;
	int infectionTime;
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
	void loadGridFromFile (string);



};

#endif /* GRID_H_ */
