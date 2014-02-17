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

}

Grid::Grid(int inputRow, int inputCol){
	population = 0;
	infected = 0;
	recovered = 0;
	susceptible = 0;
	row = inputRow;
	col = inputCol;
	int size = row * col;
	for (int i=0;i<size;i++){ // iterating through the grid vector

			Person citizen('s'); // create a person with a state of "susceptible"
			Cell oneCell; // create a cell
			oneCell.addPeople(citizen);
			// add more people to cell here
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

void Grid::updateStats(){

}

void Grid::computeGrid() {

	//int size = rows * cols;

	Grid gridTemp(row,col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			int infectedCounter = 0;
			// the cells on the edges of the grid won't check for cells outside the grid,
			// this is what the first if statements are for
			//up
			if (i > 0) {				// if it's not the first row
				if (grid.at(HelperFunctions::getIndex(i - 1, j, col)).people.at(0).healthState
						== 'i') {	// and if the cell just above is infected
					infectedCounter++;				// increment the counter
				};
			};
			//right i, j + 1, cols)
			if (j < col - 1) {				// if it's not the last column
				if (grid.at(HelperFunctions::getIndex(i, j+1, col)).people.at(0).healthState
						== 'i') {		// if the cell to the right is infected
					infectedCounter++;
				};
			}
			//down i + 1, j, cols
			if (i < row - 1) {				// if it's not the last row
				if (grid.at(HelperFunctions::getIndex(i + 1, j, col)).people.at(0).healthState
						== 'i') {		// if the cell just below is infected
					infectedCounter++;
				};
			};
			//left  i, j - 1, cols
			if (j > 0) { // if it's not the first column
				if (grid.at(HelperFunctions::getIndex(i, j-1, col)).people.at(0).healthState
						== 'i') { // if the cell to the left is infected
					infectedCounter++;
				};
			};
			char personState;
			char currentState =
					grid.at(HelperFunctions::getIndex(i, j, col)).people.at(0).healthState;
			if (infectedCounter > 1) {
				personState = 'i';
			} else {
				personState = currentState;
			}

			Person citizen(personState);
			Cell oneCell;
			oneCell.addPeople(citizen);

			gridTemp.grid.at(HelperFunctions::getIndex(i, j, col)) = oneCell;
		}
	}
	grid = gridTemp.grid;
	/*for (int i = 0; i < size; i++) {
		grid.grid.at(i) = gridTemp.grid.at(i);
	}*/

}

void Grid::saveGridToFile(string file) {
	ofstream outFile(file.c_str(), ios::out); // creating file object

	if (!outFile) {
		cerr << "File could not be opened" << endl << endl;
	}

	int size = row * col;
	outFile << row << endl;
	outFile << col << endl;
	outFile << population << endl;
	outFile << infected << endl;
	outFile << recovered << endl;
	outFile << susceptible << endl;
	for (int i = 0; i < size; i++) {
		int vectorSize = grid.at(i).people.size();
		outFile << vectorSize << endl;
		for (int j = 0; j < vectorSize; j++) {

			outFile << grid.at(i).people.at(j).healthState << endl;

		}		 // end of inner for loop

	}		 // end of outer for loop

}		 // end of method

void Grid::loadGridFromFile(string file) {

	string line;
	ifstream inFile(file.c_str());
	//ifstream inFile ("001.aut");
	//int rows, cols;
	if (inFile.is_open()) {
		inFile >> row;
		inFile >> col;
		int size = row * col;
		//Grid grid(rows,cols);
		inFile >> population;
		inFile >> infected;
		inFile >> recovered;
		inFile >> susceptible;

		//grid.grid.resize(size);
		for (int i = 0; i < size; i++) {
			int vectorSize;
			inFile >> vectorSize;
			//grid.grid.at(i).people.resize(vectorSize);
			for (int j = 0; j < vectorSize; j++) {
				inFile >> grid.at(i).people.at(j).healthState;
			}
		}
		inFile.close();
		//return grid;
	}		 // end of if file is open
	else
		cout << "Unable to open file" << endl << endl;
	//return 0;
}
