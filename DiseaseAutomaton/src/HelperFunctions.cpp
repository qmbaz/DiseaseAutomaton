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

void HelperFunctions::printGrid(Cell grid[], int rows,  int cols ) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			Cell c;
			int index= HelperFunctions::getIndex(i,j,cols);
			c = grid[index];
			int counter = c.getNumberOfPeopleInACell();
			while (counter > 0) {
				Person man;
				man = c.getPerson(counter - 1);
				char health = man.getHealthState();
				cout << health;
				counter--;
			}
			cout << " ";
		}
		cout << "\n";
	}
}

int HelperFunctions::getIndex (int r, int c, int cols){
	int i;
	i=r*cols+c;

	return i;
}
