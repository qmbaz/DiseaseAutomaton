/*
 * HelperFunctions.h
 *
 *  Created on: 17 Dec 2013
 *      Author: kuba
 */

#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

#include "Cell.h"
#include <iostream>
#include <iterator>
#include <vector>
using std::cout;
using std::cin;
using std::ios;
using std::cerr;
using std::endl;
using std::string;

#include <fstream>
using std::ofstream;
using std::ifstream;

class HelperFunctions {
public:
	HelperFunctions();
	virtual ~HelperFunctions();
	static void printGrid(Cell grid[],int, int  );
	static void computeGrid (Cell* grid, int, int);
	static void saveGridToFile (Cell* grid, int, int,string);
	static void loadGridFromFile (Cell* grid, string);
	static int getIndex(int,int,int);

};

#endif /* HELPERFUNCTIONS_H_ */
//
