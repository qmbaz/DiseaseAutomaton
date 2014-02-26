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
	Grid(int, int);
	virtual ~Grid();
	std::vector <Cell> grid;
	int row;
	int col;
	unsigned long population;
	unsigned long infected;
	unsigned long recovered;
	unsigned long susceptible;
	void updateStats();
	void printStats();
	void resetStats();//
	void printGrid();
	void computeGrid ();
	void saveGridToFile (string);
	void loadGridFromFile (string);

};

#endif /* GRID_H_ */
