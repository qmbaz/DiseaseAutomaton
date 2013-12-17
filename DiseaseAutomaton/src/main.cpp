/*
 * main.cpp
 *
 *  Created on: 1 Dec 2013
 *      Author: kuba
 */
//
#include <iostream>
#include "Cell.h"
#include "Person.h"
#include "HelperFunctions.h"

using std::cout;

#define GRID_ROWS 4
#define GRID_COLS 4


int main() {
	int rows = 10;
	int cols = 10;
	int size = rows*cols;

	HelperFunctions h;

	//cout << "one two three";
	Cell TheGrid[size];
	for (int i = 0; i < size; i++) {

			Person citizen('s');
			Cell oneCell;
			oneCell.addPeople(citizen);
			/*oneCell.addPeople(citizen);
			 oneCell.addPeople(citizen);
			 oneCell.addPeople(citizen);
			 oneCell.addPeople(citizen);*/
			TheGrid[i] = oneCell;

	}

	TheGrid[1].people.at(0).healthState='i';
	TheGrid[cols].people.at(0).healthState='i';

	//cout << TheGrid[1][0].getPerson(0).getHealthState();
	h.printGrid(TheGrid,rows,cols);
/*
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= cols; j++) {
			int index = h.getIndex(i,j,cols);
			Cell c = TheGrid[index];
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
	}*/
	cout << "\n";

	Cell TheGrid2[size];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			int infectedCounter = 0;
			//up
			if (i > 0) {
				if (TheGrid[h.getIndex(i - 1,j,cols)].getPerson(0).getHealthState() == 'i') {
					infectedCounter++;
				};
			};
			//right
			if (j < GRID_COLS) {
				if (TheGrid[h.getIndex(i,j + 1,cols)].getPerson(0).getHealthState() == 'i') {
					infectedCounter++;
				};
			}
			//down
			if (i < GRID_ROWS) {
				if (TheGrid[h.getIndex(i + 1,j,cols)].getPerson(0).getHealthState() == 'i') {
					infectedCounter++;
				};
			};
			//left
			if (j > 0) {
				if (TheGrid[h.getIndex(i,j - 1,cols)].getPerson(0).getHealthState() == 'i') {
					infectedCounter++;
				};
			};
			char personState;
			char currentState = TheGrid[h.getIndex(i,j,cols)].people.at(0).healthState;
			if (infectedCounter > 1) {
				personState = 'i';
			} else {
				personState = currentState;
			}

			Person citizen(personState);
			Cell oneCell;
			oneCell.addPeople(citizen);

			TheGrid2[h.getIndex(i,j,cols)] = oneCell;
		}
	}

	/*for (int i = 0; i < GRID_ROWS; i++) {
			for (int j = 0; j < GRID_COLS; j++) {
				Cell c = TheGrid2[i][j];
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
		}*/

		h.printGrid(TheGrid2,rows,cols);

	return 0;
}




