/*
 * HelperFunctions.cpp
 *
 *  Created on: 17 Dec 2013
 *      Author: kuba
 */

#include "HelperFunctions.h"

HelperFunctions::HelperFunctions() {
	// TODO Auto-generated constructor stub

}

HelperFunctions::~HelperFunctions() {
	// TODO Auto-generated destructor stub
}


int HelperFunctions::getIndex(int r, int c, int cols) {
	int i;
	i = r * cols + c;
	//to translate position from 2D to 1D we need row index, column index and the number of columns of the 2D array
	return i;
}
//
