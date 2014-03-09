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
#include <time.h>

using std::cout;




int main() {



	int rows = 30;
	int cols = 30;
	int iterations =20;
	int infectionTime = 10;



	/*
	 * for (int i=0;i<rows;i++){
		AGrid.grid.at(i*(cols+1)).people.at(0).healthState='i';

		}*/

	////////////////////////////////////////////////////////////////////////////////////////////////
	///////// initializing grid, setting it to a state loaded from file and printing it to screen
	////////////////////////////////////////////////////////////////////////////////////////////////
	/*Grid AGrid(rows,cols,infectionTime);
	for (int i=0;i<rows;i++){
			AGrid.grid.at(i*(cols+1)).people.at(0).healthState='i';
	}*/

	//AGrid.printGrid();
	//AGrid.saveGridToFile("begin.aut");

	Grid AGrid;
	AGrid.loadGridFromFile("begin.aut");
	AGrid.updateStats();



	///////////////////////////////////////////////////////////////////////////////////////////
	//////	iterating through "iterations" number of iterations of the cellular automaton
	/////////////////////////////////////////////////////////////////////////////////////////
	/*for (int i = 0; i <iterations; i++){
		AGrid.computeGrid();
		AGrid.updateStats();
		AGrid.printGrid();
		AGrid.printStats();
		//cout << "\n";

	}*/
	AGrid.printGrid();
	AGrid.printStats();

	return 0;
}




