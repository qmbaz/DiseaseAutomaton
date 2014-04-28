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

	unsigned int ROWS;
	unsigned int COLS;
	unsigned int ITERATIONS;
	unsigned int INFECTION_TIME;
	unsigned int PEOPLE_IN_A_CELL;
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
	string gnuplotScriptFile = "_script.";

	string filen;

	cout << "Welcome to cellular automaton based disease spread simulator"
			<< endl;
	cout << "First there will be required input for the grid initialisation"
			<< endl;
	cout << "Please enter the number of rows" << endl;
	cin >> ROWS;
	cout << "Please enter the number of columns" << endl;
	cin >> COLS;
	cout << "Please enter the number of Cellular Automaton steps" << endl;
	cin >> ITERATIONS;
	cout
			<< "Please enter the time after which an infected individual recovers or dies"
			<< endl;
	cin >> INFECTION_TIME;
	cout << "Please enter the number of people in each cell" << endl;
	cin >> PEOPLE_IN_A_CELL;
	cout << endl << "Second part is about the different factors" << endl;
	cout << "Please enter the required disease contagiousness" << endl;
	cin >> CONTAGIOUSNESS;
	cout
			<< "Please enter the required death probability for an infected individual after the infection period"
			<< endl;
	cin >> DEATH_RATE;
	cout << "Please enter the required natural death rate (per cell)" << endl;
	cin >> NATURAL_DEATH_RATE;
	cout << "Please enter the birth rate (per cell)" << endl;
	cin >> BIRTH_RATE;
	cout << endl << "The third part is the infection point" << endl;
	cout << "Please enter the row of the infected people insertion" << endl;
	cin >> INFECTION_ROW;
	cout << "Please enter the column of the infected people insertion" << endl;
	cin >> INFECTION_COL;
	cout << "Please enter the number of infected people to insert" << endl;
	cin >> INFECTION_POINT_NUMBER_OF_INFECTED;
	cout << endl << "Finally, please enter the prefix for the output files"
			<< endl;
	cin >> prefix;

	/*
	 newGr.printStats();
	 newGr.printGridPopulation();
	 newGr.infectionPoint(INFECTION_POINT_X_COORDINATE,
	 INFECTION_POINT_Y_COORDINATE,
	 INFECTION_POINT_NUMBER_OF_INFECTED);
	 newGr.printGridPopulation();
	 newGr.updateStats();
	 newGr.printStats();
	 */
	/*
	 for (unsigned int i = 0; i < ITERATIONS; i++) {
	 newGr.computeGrid();
	 //newGr.printGridPopulation();
	 newGr.updateStats();
	 newGr.printStats();
	 }
	 */

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
	plotScriptFile << "\""<< prefix + recoveredPopulationFile <<"\" title 'recovered' with linespoints, \\"<<endl;
	plotScriptFile << "\""<< prefix + susceptiblePopulationFile <<"\" title 'susceptible' with linespoints, \\"<<endl;
	plotScriptFile << "\""<< prefix + allPopulationFile <<"\" title 'population' with linespoints, \\"<<endl;
	/*
	 set title "Disease spread"
	 set xlabel "time steps"
	 set ylabel "number of people"
	 plot "infectedPlot.dat" title 'infected' with linespoints, \
			"recoveredPlot.dat" title 'recovered' with linespoints, \
			"susceptiblePlot.dat" title 'susceptible' with linespoints, \
			"allPlot.dat" title 'population' with linespoints
	 */
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

int main(int argc, char* argv[]) {

	/*
	 unsigned int ROWS = 5;
	 unsigned int COLS = 5;
	 unsigned int ITERATIONS = 20;
	 unsigned int INFECTION_TIME = 10;
	 unsigned int PEOPLE_IN_A_CELL = 2;
	 float CONTAGIOUSNESS = 0;
	 float DEATH_RATE = 0;
	 float NATURAL_DEATH_RATE = 0.1;
	 float BIRTH_RATE = 0;
	 int INFECTION_POINT_X_COORDINATE = 3;
	 int INFECTION_POINT_Y_COORDINATE = 3;
	 int INFECTION_POINT_NUMBER_OF_INFECTED = 0;
	 string filen = "belgium";
	 string infectedPopulationFile = "infectedPlot.dat";
	 string susceptiblePopulationFile = "susceptiblePlot.dat";
	 string recoveredPopulationFile = "recoveredPlot.dat";
	 string allPopulationFile = "allPlot.dat";
	 */
	if (argc > 1) {
		if (string(argv[1]) == "wizard") {
			wizard();
		}
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
	 newGr.grid.at(i*(COLS+1)).people.at(0).healthState='i';

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
	 Grid newGr;
	 newGr.loadGridFromFile("begin.aut");
	 newGr.updateStats();

	 cout << "beginning state" << endl;
	 */

	//newGr.printGrid();
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

	 infectedPlotFile << 0 << " " << newGr.infected << endl;
	 susceptiblePlotFile << 0 << " " << newGr.susceptible << endl;
	 recoveredPlotFile << 0 << " " << newGr.recovered << endl;
	 allPlotFile << 0 << " " << newGr.population << endl;

	 for (int i = 0; i < ITERATIONS; i++) {
	 cout << "iteration " << i + 1 << endl << endl;
	 newGr.computeGrid();
	 newGr.updateStats();

	 infectedPlotFile << i + 1 << " " << newGr.infected << endl;
	 susceptiblePlotFile << i + 1 << " " << newGr.susceptible << endl;
	 recoveredPlotFile << i + 1 << " " << newGr.recovered << endl;
	 allPlotFile << i + 1 << " " << newGr.population << endl;

	 newGr.printGrid();
	 newGr.printStats();
	 //cout << "\n";

	 }
	 //newGr.printGrid();
	 //newGr.printStats();

	 */

	return 0;
}

