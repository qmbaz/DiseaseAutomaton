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
using std::cout;

class HelperFunctions {
public:
	HelperFunctions();
	virtual ~HelperFunctions();
	void printGrid(Cell grid[],int, int  );
	static int getIndex(int,int,int);
};

#endif /* HELPERFUNCTIONS_H_ */
