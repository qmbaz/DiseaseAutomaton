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




int main() {


	//HelperFunctions h;

	//cout << "one two three";
	int rows = 20;
	int cols = 20;
	int size = rows*cols;
	Cell TheGrid[size]; // creating a grid in the form of array of size "size"
	for (int i = 0; i < size; i++) {

			Person citizen('s'); // create a person with a state of "susceptible"
			Cell oneCell; // create a cell
			oneCell.addPeople(citizen); // add the previously created person to a cell
			/*oneCell.addPeople(citizen);
			 oneCell.addPeople(citizen);
			 oneCell.addPeople(citizen);
			 oneCell.addPeople(citizen);*/
			TheGrid[i] = oneCell; // add the cell to the TheGrid array in the position of "i"

	}

	// modifying the healthstate of two people to get an initial state of the cellular automaton

//	TheGrid[1].people.at(0).healthState='i';
	//TheGrid[cols].people.at(0).healthState='i'; // cols is a number of columns, so as the position is counted from 0, this is the
	// first position in the second row
	for (int i=0;i<rows;i++){
	TheGrid[i*(cols+1)].people.at(0).healthState='i';

	}
	HelperFunctions::printGrid(TheGrid,rows,cols);
	cout << "\n";
	for (int i = 0; i <20; i++){
		HelperFunctions::computeGrid(TheGrid,rows,cols);
		HelperFunctions::printGrid(TheGrid,rows,cols);
		cout << "\n";

	}

	return 0;
}




