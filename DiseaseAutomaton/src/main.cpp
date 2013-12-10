/*
 * main.cpp
 *
 *  Created on: 1 Dec 2013
 *      Author: kuba
 */

#include <iostream>
#include "Cell.h"
#include "Person.h"

using std::cout;

#define GRID_ROWS 4
#define GRID_COLS 4

int main() {
	//cout << "one two three";
	Cell TheGrid[GRID_ROWS][GRID_COLS];
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLS; j++) {
			Person citizen('s');
			Cell oneCell;
			oneCell.addPeople(citizen);
			/*oneCell.addPeople(citizen);
			 oneCell.addPeople(citizen);
			 oneCell.addPeople(citizen);
			 oneCell.addPeople(citizen);*/
			TheGrid[i][j] = oneCell;
		}
	}

	TheGrid[0][1].people.at(0).healthState='i';
	TheGrid[1][0].people.at(0).healthState='i';

	//cout << TheGrid[1][0].getPerson(0).getHealthState();

	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLS; j++) {
			Cell c = TheGrid[i][j];
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
	cout << "\n";

	Cell TheGrid2[GRID_ROWS][GRID_COLS];
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLS; j++) {

			int infectedCounter = 0;
			//up
			if (i > 0) {
				if (TheGrid[i - 1][j].getPerson(0).getHealthState() == 'i') {
					infectedCounter++;
				};
			};
			//right
			if (j < GRID_COLS) {
				if (TheGrid[i][j + 1].getPerson(0).getHealthState() == 'i') {
					infectedCounter++;
				};
			}
			//down
			if (i < GRID_ROWS) {
				if (TheGrid[i + 1][j].getPerson(0).getHealthState() == 'i') {
					infectedCounter++;
				};
			};
			//left
			if (j > 0) {
				if (TheGrid[i][j - 1].getPerson(0).getHealthState() == 'i') {
					infectedCounter++;
				};
			};
			char personState;
			char currentState = TheGrid[i][j].people.at(0).healthState;
			if (infectedCounter > 1) {
				personState = 'i';
			} else {
				personState = currentState;
			}

			Person citizen(personState);
			Cell oneCell;
			oneCell.addPeople(citizen);

			TheGrid2[i][j] = oneCell;
		}
	}

	for (int i = 0; i < GRID_ROWS; i++) {
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
		}


	return 0;
}

