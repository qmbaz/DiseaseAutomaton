/*
 * main.cpp
 *
 *  Created on: 1 Dec 2013
 *      Author: kuba
 */
//
#include <iostream>
#include <fstream>
#include "Cell.h"
#include "Person.h"
#include "HelperFunctions.h"
#include <time.h>

using std::cout;
using std::ofstream;
using std::ios;
using std::string;

void testLoading(){//
	Grid tGrid;
		tGrid.loadGridFromFile("multiple.dat");
		for (int i=0;i<(tGrid.row*tGrid.col);i++){
			cout << "cell no " << i << endl;
			for (int j=0;j<tGrid.grid.at(i).getNumberOfPeopleInACell();j++){
				cout << "person no " << j << " state is " << tGrid.grid.at(i).people.at(j).getHealthState() << endl;
			}

		}
}


void testCreate(int ROWS, int COLS, int INFECTION_TIME, int PEOPLE_IN_A_CELL, string filen, float infecRate){
	Grid aGrid (ROWS,COLS,INFECTION_TIME,PEOPLE_IN_A_CELL,infecRate);
		aGrid.saveGridToFile(filen+"_initial");
}

int main() {

	int ROWS = 30;
	int COLS = 30;
	int ITERATIONS = 20;
	int INFECTION_TIME = 10;
	int PEOPLE_IN_A_CELL = 10;
	float CONTAGIOUSNESS = 0.02;
	int INFECTION_POINT_X_COORDINATE = 3;
	int INFECTION_POINT_Y_COORDINATE = 3;
	int INFECTION_POINT_NUMBER_OF_INFECTED = 5;
	string filen = "belgium";
	string infectedPopulationFile = "infectedPlot.dat";
	string susceptiblePopulationFile = "susceptiblePlot.dat";
	string recoveredPopulationFile = "recoveredPlot.dat";
	string allPopulationFile = "allPlot.dat";

Grid newGr(ROWS,COLS, INFECTION_TIME,PEOPLE_IN_A_CELL, CONTAGIOUSNESS);
newGr.updateStats();
newGr.printStats();
newGr.printGridInfected();
newGr.infectionPoint(INFECTION_POINT_X_COORDINATE,INFECTION_POINT_Y_COORDINATE,INFECTION_POINT_NUMBER_OF_INFECTED);
newGr.printGridInfected();
newGr.updateStats();
newGr.printStats();

for (int i=0;i< ITERATIONS;i++){
	newGr.computeGrid();
	newGr.printGridInfected();
	newGr.updateStats();
	newGr.printStats();
}

/*
	//testLoading();
	testCreate (ROWS, COLS, INFECTION_TIME, PEOPLE_IN_A_CELL,filen, 0.001);
	Grid tGrid;
			tGrid.loadGridFromFile(filen);
	for (unsigned int n=0;n<tGrid.grid.at(0).people.size();n++){
		tGrid.grid.at(0).people.at(n).healthState='i';
		tGrid.grid.at(0).people.at(n).timeTillRecovered=INFECTION_TIME;
	}
	tGrid.updateStats();
	tGrid.printStats();
	tGrid.computeGrid();
	tGrid.updateStats();
	tGrid.printStats();
	tGrid.saveGridToFile("multipleComputed.dat");
*/

	/*
	 * for (int i=0;i<ROWS;i++){
	 AGrid.grid.at(i*(COLS+1)).people.at(0).healthState='i';

	 }*/

	////////////////////////////////////////////////////////////////////////////////////////////////
	///////// creating initial state of the automaton, displaying it to screen and saving to disk
	////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	 Grid TheGrid(ROWS,COLS,INFECTION_TIME);
	 for (int i=0;i<ROWS;i++){
	 TheGrid.grid.at(i*(COLS+1)).people.at(0).healthState='i';
	 TheGrid.grid.at(i*(COLS+1)).people.at(0).timeTillRecovered= INFECTION_TIME;
	 }

	 TheGrid.printGrid();
	 TheGrid.saveGridToFile("begin.aut");
	 //*/

/*
	////////////////////////////////////////////////////////////////////////////////////////////////
	///////// initializing grid, setting it to a state loaded from file and printing it to screen
	////////////////////////////////////////////////////////////////////////////////////////////////
	Grid AGrid;
	AGrid.loadGridFromFile("begin.aut");
	AGrid.updateStats();

	cout << "beginning state" << endl;
	*/

	//AGrid.printGrid();
/*
	///////////////////////////////////////////////////////////////////////////////////////////
	//////	iterating through "ITERATIONS" number of ITERATIONS of the cellular automaton
	/////////////////////////////////////////////////////////////////////////////////////////
	ofstream infectedPlotFile(infectedPopulationFile.c_str(), ios::out); // creating file object
	if (!infectedPlotFile) {
		cerr << "infected population file could not be opened" << endl << endl;
	}

	ofstream susceptiblePlotFile(susceptiblePopulationFile.c_str(), ios::out);
	if (!susceptiblePlotFile) {
		cerr << "susceptible population file could not be opened" << endl
				<< endl;
	}

	ofstream recoveredPlotFile(recoveredPopulationFile.c_str(), ios::out);
	if (!recoveredPlotFile) {
		cerr << "recovered population file could not be opened" << endl << endl;
	}

	ofstream allPlotFile(allPopulationFile.c_str(), ios::out);
	if (!allPlotFile) {
		cerr << "all population file could not be opened" << endl << endl;
	}

	infectedPlotFile << 0 << " " << AGrid.infected << endl;
	susceptiblePlotFile << 0 << " " << AGrid.susceptible << endl;
	recoveredPlotFile << 0 << " " << AGrid.recovered << endl;
	allPlotFile << 0 << " " << AGrid.population << endl;

	for (int i = 0; i < ITERATIONS; i++) {
		cout << "iteration " << i + 1 << endl << endl;
		AGrid.computeGrid();
		AGrid.updateStats();

		infectedPlotFile << i + 1 << " " << AGrid.infected << endl;
		susceptiblePlotFile << i + 1 << " " << AGrid.susceptible << endl;
		recoveredPlotFile << i + 1 << " " << AGrid.recovered << endl;
		allPlotFile << i + 1 << " " << AGrid.population << endl;

		AGrid.printGrid();
		AGrid.printStats();
		//cout << "\n";

	}
	//AGrid.printGrid();
	//AGrid.printStats();

*/

	return 0;
}


