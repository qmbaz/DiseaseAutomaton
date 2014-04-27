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

int HelperFunctions::testAndSetCoordinate(int coor, int max, string introText, string coorName) {
	coor--;
	if (coor < 0) {
		coor = 0;
		cout << introText << "the " << coorName
				<< " coordinate is less than 1 --> set to the minimum value of 1"
				<< endl;

	}
	if (coor >= max) {
		coor = max - 1;
		cout << introText << "the " << coorName
				<< " coordinate too large --> reduced to maximum value of "
				<< max << endl;

	}
	return coor;
}
