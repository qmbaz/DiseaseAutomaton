/*
 * HelperFunctions.h
 *
 *  Created on: 17 Dec 2013
 *      Author: kuba
 */

#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

#include "Cell.h"
#include "Grid.h"
#include <iostream>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <time.h>
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
	//static void printGrid(Grid,int, int  );
	//static Grid computeGrid (Grid, int, int);
	//static void saveGridToFile (Grid, int, int, string);
	//static Grid loadGridFromFile (string);
	static int getIndex(int, int, int);
	static int testAndSetCoordinate(int, int, string, string);
	static unsigned long timeVal();
	static bool stochastic(float cntg, int count);
};

#endif /* HELPERFUNCTIONS_H_ */
//
