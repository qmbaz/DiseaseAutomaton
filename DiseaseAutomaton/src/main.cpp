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

int main() {

	int rows = 30;
	int cols = 30;
	int iterations = 40;
	int infectionTime = 10;
	string infectedPopulationFile = "infectedPlot.dat";
	string susceptiblePopulationFile = "susceptiblePlot.dat";
	string recoveredPopulationFile = "recoveredPlot.dat";
	string allPopulationFile = "allPlot.dat";

	/*
	 * for (int i=0;i<rows;i++){
	 AGrid.grid.at(i*(cols+1)).people.at(0).healthState='i';

	 }*/

	////////////////////////////////////////////////////////////////////////////////////////////////
	///////// creating initial state of the automaton, displaying it to screen and saving to disk
	////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	 Grid TheGrid(rows,cols,infectionTime);
	 for (int i=0;i<rows;i++){
	 TheGrid.grid.at(i*(cols+1)).people.at(0).healthState='i';
	 TheGrid.grid.at(i*(cols+1)).people.at(0).timeTillRecovered= infectionTime;
	 }

	 TheGrid.printGrid();
	 TheGrid.saveGridToFile("begin.aut");
	 //*/

	////////////////////////////////////////////////////////////////////////////////////////////////
	///////// initializing grid, setting it to a state loaded from file and printing it to screen
	////////////////////////////////////////////////////////////////////////////////////////////////
	Grid AGrid;
	AGrid.loadGridFromFile("begin.aut");
	AGrid.updateStats();

	cout << "beginning state" << endl;
	AGrid.printGrid();

	///////////////////////////////////////////////////////////////////////////////////////////
	//////	iterating through "iterations" number of iterations of the cellular automaton
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

	for (int i = 0; i < iterations; i++) {
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

	return 0;
}

