/*
 * Grid.cpp
 *
 *  Created on: 11 Feb 2014
 *      Author: kuba
 */

#include "Grid.h"

Grid::Grid() {
	// TODO Auto-generated constructor stub
	population = 0;
	infected = 0;
	recovered = 0;
	susceptible = 0;
	row = 0;
	col = 0;
	infectionTime = 0;
	peopleInACell = 0;

}

Grid::Grid(int inputRow, int inputCol, int infTime, int pInACell) {
	population = 0;
	infected = 0;
	recovered = 0;
	susceptible = 0;
	row = inputRow;
	col = inputCol;
	infectionTime = infTime;
	peopleInACell = pInACell;
	unsigned long size = row * col;
	for (unsigned long i = 0; i < size; i++) { // iterating through the grid vector
		Cell oneCell; // create a cell

		for (int j = 0; j < peopleInACell; j++) {
			Person citizen('s'); // create a person with a state of "susceptible"
			citizen.timeTillRecovered = -1;
			oneCell.addPeople(citizen);
			// add more people to cell here

		}
		grid.push_back(oneCell);
	}

}

Grid::~Grid() {
// TODO Auto-generated destructor stub
}

void Grid::printGrid() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			Cell c;
			int index = HelperFunctions::getIndex(i, j, col);
			c = grid.at(index);
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
}

void Grid::printGridStat(char statType) {
	bool printNotAll = true;
	if (statType == 'a')
		printNotAll = false;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			Cell c;
			int index = HelperFunctions::getIndex(i, j, col);
			c = grid.at(index);
			int counter = c.getNumberOfPeopleInACell();
			int stat = 0;
			if (printNotAll) {

				while (counter > 0) {
					Person man;
					man = c.getPerson(counter - 1);
					char health = man.getHealthState();
					if (health == statType)
						stat++;
					counter--;
				}
			} else {
				stat = counter;
			}
			char num_section[3];
			sprintf(num_section, "%03d", stat);
			string cellStat(num_section);
			cout << cellStat + " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void Grid::printGridInfected() {
	cout << "Grid of the Infected\n\n";
	printGridStat('i');
}
void Grid::printGridSusceptible() {
	cout << "Grid of the Susceptible\n\n";
	printGridStat('s');
}
void Grid::printGridRecovered() {
	cout << "Grid of the Recovered\n\n";
	printGridStat('r');
}

void Grid::printGridPopulation() {
	cout << "Grid of the Population numbers\n\n";
	printGridStat('a');
}

void Grid::printAllPeopleStates() {
	for (int i = 0; i < (row * col); i++) {
		cout << "cell no " << i << endl;
		for (int j = 0; j < grid.at(i).getNumberOfPeopleInACell(); j++) {
			cout << "person no " << j << " state is "
					<< grid.at(i).people.at(j).getHealthState() << endl;
		}

	}
}

void Grid::infectionPoint(int ro, int co, int num) { // row and column coordinates numbered from 1
	ro--;//
	co--;// conversion from coordinates numbered from 1 to numbered from 0 - which is demanded by HelperFunctions:getIndex

	if (ro < 0) {
		ro = 0;
		cout
				<< "Infection point: the row coordinate is less than 1 --> set to the minimum value of 1"
				<< endl;

	}

	if (co < 0) {
		co = 0;
		cout
				<< "Infection point: the column coordinate is less than 1 --> set to the minimum value of 1"
				<< endl;

	}

	if (ro >= row) {
		ro = row - 1;
		cout << "Infection point: the row coordinate too large --> reduced to maximum value of "
				<< row << endl;

	}

	if (co >= col) {
		co = col - 1;
		cout
				<< "Infection point: the column coordinate too large --> reduced to maximum value of "
				<< col << endl;

	}

	unsigned long position = HelperFunctions::getIndex(ro, co, col);
	Person infected('i');
	infected.timeTillRecovered = infectionTime;
	for (int i = 0; i < num; i++) {

		grid.at(position).addPeople(infected);
	}

}

void Grid::updateStats() {
	resetStats();
//
	unsigned long size = row * col;
	for (unsigned long i = 0; i < size; i++) {
		for (unsigned long j = 0; j < grid.at(i).people.size(); j++) {
			population++;
			char state = grid.at(i).people.at(j).healthState;
			switch (state) {
			case 's':
				susceptible++;
				break;
			case 'i':
				infected++;
				break;
			case 'r':
				recovered++;
				break;
			}
		}
	}
}

void Grid::printStats() {
	cout << endl;
	cout << "population:	" << population << endl;
	cout << "susceptible:	" << susceptible << endl;
	cout << "infected:	" << infected << endl;
	cout << "recovered:	" << recovered << endl;
	cout << endl;
}

void Grid::resetStats() {
	population = 0;
	susceptible = 0;
	infected = 0;
	recovered = 0;
}

void Grid::computeGrid() {

	struct timespec start, stop;
	long int execTime;
	clock_gettime(CLOCK_MONOTONIC, &start);
	Grid gridTemp(row, col, infectionTime, 0);
	for (int i = 0; i < row; i++) { // iterate through rows
		for (int j = 0; j < col; j++) { // iterate through columns
			Cell oneCell;
			for (int numC = 0; //numC - number of current cell person
			numC < grid.at(HelperFunctions::getIndex(i, j, col)).people.size();
					numC++) { // iterate through people in a cell of coordinates i,j
				int infectedCounter = 0;
				// the cells on the edges of the grid won't check for cells outside the grid,
				// this is what the first if statements are for
				//up

				if (i > 0) {				// if it's not the first row
					for (int numN = 0;// numN - number of a person in a neighbouring cell
							numN
									< grid.at(
											HelperFunctions::getIndex(i - 1, j,
													col)).people.size();
							numN++) {
						if (grid.at(HelperFunctions::getIndex(i - 1, j, col)).people.at(
								numN).healthState == 'i') {	// and if the cell just above is infected
							infectedCounter++;			// increment the counter
						};
					};
				};

				//right i, j + 1, cols)

				if (j < col - 1) {			// if it's not the last column
					for (int numN = 0;
							numN
									< grid.at(
											HelperFunctions::getIndex(i, j + 1,
													col)).people.size();
							numN++) {
						if (grid.at(HelperFunctions::getIndex(i, j + 1, col)).people.at(
								numN).healthState == 'i') {	// if the cell to the right is infected
							infectedCounter++;
						};
					};
				};

				//down i + 1, j, cols

				if (i < row - 1) {				// if it's not the last row
					for (int numN = 0;
							numN
									< grid.at(
											HelperFunctions::getIndex(i + 1, j,
													col)).people.size();
							numN++) {
						if (grid.at(HelperFunctions::getIndex(i + 1, j, col)).people.at(
								numN).healthState == 'i') {	// if the cell just below is infected
							infectedCounter++;
						};
					};
				};

				//left  i, j - 1, cols
				if (j > 0) { // if it's not the first column
					for (int numN = 0;
							numN
									< grid.at(
											HelperFunctions::getIndex(i, j - 1,
													col)).people.size();
							numN++) {
						if (grid.at(HelperFunctions::getIndex(i, j - 1, col)).people.at(
								numN).healthState == 'i') { // if the cell to the left is infected
							infectedCounter++;
						};
					};
				};
				Person newPerson;

				Person currentPerson = grid.at(
						HelperFunctions::getIndex(i, j, col)).people.at(numC);

				/////// if current person is susceptible ('s')
				if (currentPerson.healthState == 's') {
					if (infectedCounter > 1) { // this will need to be changed for a better way of determining if a person gets infected
						newPerson.healthState = 'i';
						newPerson.timeTillRecovered = infectionTime;
						//	personState

					} else {
						newPerson.healthState = currentPerson.healthState; // which means it's still 's'
					}
				}

				/////// if current person is infective ('i')
				else if (currentPerson.healthState == 'i') {
					newPerson = currentPerson;
					newPerson.timeTillRecovered--;
					//currentPerson.timeTillRecovered--;
					if (currentPerson.timeTillRecovered <= 0) {
						newPerson.healthState = 'r';
					}
				}

				//////  if current person is recovered with immunity ('r')
				else if (currentPerson.healthState == 'r') {
					newPerson = currentPerson;
				}
				oneCell.addPeople(newPerson);
			};

			/////// adding new cell to the temporary grid
			//Person citizen(personState);

			gridTemp.grid.at(HelperFunctions::getIndex(i, j, col)) = oneCell;
		}
	}
	grid = gridTemp.grid;
	clock_gettime(CLOCK_MONOTONIC, &stop);
//execTime = (stop.tv_sec - start.tv_sec)
//		+  (stop.tv_nsec - start.tv_nsec) * 1e-6;
	execTime = stop.tv_nsec - start.tv_nsec;
	cout << endl << "Execution time in nanoseconds: " << execTime //try changing 1e-9 in the line above instead 1000 here -- done
			<< endl;
	/*cout << endl << "start time is: " << start << endl;
	 cout <<endl << "end time is: " << finish << endl;
	 cout << endl << "compute time is: "<< computeTime << endl << endl;*/

	/*for (int i = 0; i < size; i++) {
	 grid.grid.at(i) = gridTemp.grid.at(i);
	 }*/

}

void Grid::saveGridToFile(string file) {
	ofstream outFile(file.c_str(), ios::out); // creating file object

	if (!outFile) {
		cerr << "File could not be opened" << endl << endl;
	}

	unsigned long size = row * col;
	outFile << row << endl;
	outFile << col << endl;
	outFile << infectionTime << endl;
	outFile << population << endl;
	outFile << infected << endl;
	outFile << recovered << endl;
	outFile << susceptible << endl;
	for (unsigned long i = 0; i < size; i++) {
		int vectorSize = grid.at(i).people.size();
		outFile << vectorSize << endl;
		for (int j = 0; j < vectorSize; j++) {

			outFile << grid.at(i).people.at(j).healthState << endl; // put in timeTillRecoveredh as well
			outFile << grid.at(i).people.at(j).timeTillRecovered << endl;
		}		 // end of inner for loop

	}		 // end of outer for loop

}		 // end of method

void Grid::loadGridFromFile(string file) {

//Grid tempGrid;
	string line;
	ifstream inFile(file.c_str());
//ifstream inFile ("001.aut");
//int rows, cols;
	if (inFile.is_open()) {
		//int rows, cols, infTime;
		inFile >> row;
		inFile >> col;
		inFile >> infectionTime;
		int size = row * col;
		//Grid grid(rows,cols);
		//inFile >> infectionTime;
		grid.resize(size);
		//Grid tempGrid(rows,cols,infTime);
		inFile >> population;
		inFile >> infected;
		inFile >> recovered;
		inFile >> susceptible;

		//grid.grid.resize(size);
		for (unsigned long i = 0; i < size; i++) {
			int vectorSize;
			inFile >> vectorSize;
			grid.at(i).people.resize(vectorSize);
			for (int j = 0; j < vectorSize; j++) {
				inFile >> grid.at(i).people.at(j).healthState;
				inFile >> grid.at(i).people.at(j).timeTillRecovered;
			}
		}
		inFile.close();

	}		 // end of if file is open
	else
		cout << "Unable to open file" << endl << endl;

}
