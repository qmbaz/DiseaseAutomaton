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

void testLoading() { //
	Grid tGrid;
	tGrid.loadGridFromFile("multiple.dat");
	for (unsigned int i = 0; i < (tGrid.row * tGrid.col); i++) {
		cout << "cell no " << i << endl;
		for (int j = 0; j < tGrid.grid.at(i).getNumberOfPeopleInACell(); j++) {
			cout << "person no " << j << " state is "
					<< tGrid.grid.at(i).people.at(j).getHealthState() << endl;
		}

	}
}

void testCreate(int ROWS, int COLS, int INFECTION_TIME, int PEOPLE_IN_A_CELL,
		string filen, float infecRate, float deathRate, float birthRate,
		float natBirthRate) {
	Grid newGr(ROWS, COLS, INFECTION_TIME, PEOPLE_IN_A_CELL, infecRate,
			deathRate, birthRate, natBirthRate);
	newGr.saveGridToFile(filen + "_initial");
}

void wizard() {

	int ROWS;
	int COLS;
	int ITERATIONS;
	int INFECTION_TIME;
	int PEOPLE_IN_A_CELL;
	float CONTAGIOUSNESS;
	float DEATH_RATE;
	float NATURAL_DEATH_RATE;
	float BIRTH_RATE;
	int INFECTION_ROW;
	int INFECTION_COL;
	int INFECTION_POINT_NUMBER_OF_INFECTED;
	string prefix;
	string infectedPopulationFile = "_infectedPlot.dat";
	string susceptiblePopulationFile = "_susceptiblePlot.dat";
	string recoveredPopulationFile = "_recoveredPlot.dat";
	string allPopulationFile = "_populationPlot.dat";
	string gnuplotScriptFile = "_script.p";

	string filen;

	cout << "Welcome to cellular automaton based disease spread simulator"
			<< endl;
	cout << "First there will be required input for the grid initialisation"
			<< endl;
	cout << "Please enter the number of rows (int)" << endl;
	cin >> ROWS;
	cout << "Please enter the number of columns (int)" << endl;
	cin >> COLS;
	cout << "Please enter the number of Cellular Automaton steps (int)" << endl;
	cin >> ITERATIONS;
	cout
			<< "Please enter the time after which an infected individual recovers or dies (int)"
			<< endl;
	cin >> INFECTION_TIME;
	cout << "Please enter the number of people in each cell(int)" << endl;
	cin >> PEOPLE_IN_A_CELL;
	cout << endl << "Second part is about the different factors" << endl;
	cout << "Please enter the required disease contagiousness (float)" << endl;
	cin >> CONTAGIOUSNESS;
	cout
			<< "Please enter the required death probability for an infected individual after the infection period"
			<< endl;
	cin >> DEATH_RATE;
	cout << "Please enter the required natural death rate - per person(float)"
			<< endl;
	cin >> NATURAL_DEATH_RATE;
	cout << "Please enter the birth rate - per cell (float)" << endl;
	cin >> BIRTH_RATE;
	cout << endl << "The third part is the infection point" << endl;
	cout << "Please enter the row of the infected people insertion (int)"
			<< endl;
	cin >> INFECTION_ROW;
	cout << "Please enter the column of the infected people insertion (int)"
			<< endl;
	cin >> INFECTION_COL;
	cout << "Please enter the number of infected people to insert (input)"
			<< endl;
	cin >> INFECTION_POINT_NUMBER_OF_INFECTED;
	cout << endl
			<< "Finally, please enter the prefix for the output files (string)"
			<< endl;
	cin >> prefix;

	//// creating the grid
	/////////////////////////////
	Grid newGr(ROWS, COLS, INFECTION_TIME, PEOPLE_IN_A_CELL, CONTAGIOUSNESS,
			DEATH_RATE, BIRTH_RATE, NATURAL_DEATH_RATE);
	newGr.updateStats();
	cout << endl << "initial state" << endl;
	newGr.printStats();

	//// insertion of a number of infected individuals at the specified point in the grid
	///////////////////////////////////////////////////////////////////////////////////////
	newGr.infectionPoint(INFECTION_ROW, INFECTION_COL,
			INFECTION_POINT_NUMBER_OF_INFECTED);
	newGr.updateStats();
	cout << endl << "state after infection" << endl;
	newGr.printStats();

	int n = 0;
	char num_section[5];
	sprintf(num_section, "%05d", n);
	string file_num(num_section);
	filen = prefix + file_num;

	newGr.saveGridToFile(filen);

	//// creation of the plot files
	/////////////////////////////////////////////

	// the plot script file
	ofstream plotScriptFile((prefix + gnuplotScriptFile).c_str(), ios::out); // creating file object
	if (!plotScriptFile) {
		cerr << "plot script file could not be opened" << endl << endl;
	}

	// the plot files
	ofstream infectedPlotFile((prefix + infectedPopulationFile).c_str(),
			ios::out); // creating file object
	if (!infectedPlotFile) {
		cerr << "infected population file could not be opened" << endl << endl;
	}

	ofstream susceptiblePlotFile((prefix + susceptiblePopulationFile).c_str(),
			ios::out);
	if (!susceptiblePlotFile) {
		cerr << "susceptible population file could not be opened" << endl
				<< endl;
	}

	ofstream recoveredPlotFile((prefix + recoveredPopulationFile).c_str(),
			ios::out);
	if (!recoveredPlotFile) {
		cerr << "recovered population file could not be opened" << endl << endl;
	}

	ofstream allPlotFile((prefix + allPopulationFile).c_str(), ios::out);
	if (!allPlotFile) {
		cerr << "all population file could not be opened" << endl << endl;
	}
	////////////////////////////////////////////////////////

	//// initial lines of the plot files
	/////////////////////////////////////////
	infectedPlotFile << 0 << " " << newGr.infected << endl;
	susceptiblePlotFile << 0 << " " << newGr.susceptible << endl;
	recoveredPlotFile << 0 << " " << newGr.recovered << endl;
	allPlotFile << 0 << " " << newGr.population << endl;

	// contents of the script file
	plotScriptFile << "set title \"Disease spread\"" << endl;
	plotScriptFile << "set xlabel \"time steps\"" << endl;
	plotScriptFile << "set ylabel \"number of people\"" << endl;
	plotScriptFile << "plot \"" << prefix + infectedPopulationFile
			<< "\" title 'infected' with linespoints, \\" << endl;
	plotScriptFile << "\"" << prefix + recoveredPopulationFile
			<< "\" title 'recovered' with linespoints, \\" << endl;
	plotScriptFile << "\"" << prefix + susceptiblePopulationFile
			<< "\" title 'susceptible' with linespoints, \\" << endl;
	plotScriptFile << "\"" << prefix + allPopulationFile
			<< "\" title 'population' with linespoints, \\" << endl;

	//// iteration through the Cellular Automaton steps: computing the steps, updating statistics and saving to plot files and automaton files
	//////////////////////////////////////////////////
	for (int i = 0; i < ITERATIONS; i++) {
		cout << "iteration " << i + 1 << endl << endl;
		newGr.computeGrid();
		newGr.updateStats();

		char num_section[5];
		sprintf(num_section, "%05d", i + 1);
		string file_num(num_section);
		filen = prefix + file_num;

		newGr.saveGridToFile(filen);

		infectedPlotFile << i + 1 << " " << newGr.infected << endl;
		susceptiblePlotFile << i + 1 << " " << newGr.susceptible << endl;
		recoveredPlotFile << i + 1 << " " << newGr.recovered << endl;
		allPlotFile << i + 1 << " " << newGr.population << endl;

		newGr.printStats();
		//newGr.saveGridToFile()

		//cout << "\n";

	}

}

void usage() {
	cout
			<< "Simulating the Spread of Infectious Disease Using a Cellular Automaton Framework"
			<< endl;
	cout << "B00045505 Jakub Suchecki, 2014" << endl << endl;
	cout << "Usage:" << endl << endl;
	cout
			<< "-wizard or -w	: starts a wizard which asks user for all the parameters"
			<< endl
			<< "		and creates an initial state of cellular automaton and then"
			<< endl << "		runs the automaton specified number of times" << endl;
	cout << "-ps	<filename>: Print Stats" << endl
			<< "		shows the statistics of the state of the cellular" << endl
			<< "		automaton saved in the file specifies with the <filename>"
			<< endl;
	cout << "-pgi	<filename>: Print Grid Infected" << endl
			<< "		prints the numbers of infected in each cell in the form "
			<< endl << "		of a grid (suitable only for small grids)" << endl;
	cout << "-pgs	<filename>: Print Grid Susceptible" << endl
			<< "		prints the numbers of susceptible in each cell in the form"
			<< endl << " 		of a grid (suitable only for small grids)" << endl;
	cout << "-pgr	<filename>: Prind Grid Recovered" << endl
			<< "		prints the numbers of recovered in each cell in the form"
			<< endl << " 		of a grid (suitable only for small grids)" << endl;
	cout << "-pgp	<filename>: Print Grid People" << endl
			<< "		prints the numbers of people in each cell in the form" << endl
			<< "		 of a grid (suitable only for small grids)" << endl;
	cout << "-paps	<filename>: Print All People States" << endl
			<< "		prints out the states of all the people in the grid," << endl
			<< "		line by line" << endl << endl;
}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		usage();
	} else if (argc > 1) {
		if (string(argv[1]) == "-wizard" || string(argv[1]) == "-w") {
			wizard();
		} else if (argc > 2) {
			if (string(argv[1]) == "-ps") {
				Grid newGr;
				if (newGr.loadGridFromFile(argv[2])) {
					newGr.printStats();
				}
			} else if (string(argv[1]) == "-pgi") {
				Grid newGr;
				if (newGr.loadGridFromFile(argv[2])) {
					newGr.printGridInfected();
				}
			} else if (string(argv[1]) == "-pgs") {
				Grid newGr;
				if (newGr.loadGridFromFile(argv[2])) {
					newGr.printGridSusceptible();
				}
			} else if (string(argv[1]) == "-pgr") {
				Grid newGr;
				if (newGr.loadGridFromFile(argv[2])) {
					newGr.printGridRecovered();
				}
			} else if (string(argv[1]) == "-pgp") {
				Grid newGr;
				if (newGr.loadGridFromFile(argv[2])) {
					newGr.printGridPopulation();
				}
			} else if (string(argv[1]) == "-paps") {
				Grid newGr;
				if (newGr.loadGridFromFile(argv[2])) {
					newGr.printAllPeopleStates();
				}
			} else {
				cout << "Unknown argument" << endl;
				usage();
			}
		} else {
			usage();
		}
	}
	return 0;
}
