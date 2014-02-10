/*
 * HelperFunctions.cpp
 *
 *  Created on: 17 Dec 2013
 *      Author: kuba
 */

#include "HelperFunctions.h"

HelperFunctions::HelperFunctions() {
	// TODO Auto-generated constructor stub

}

HelperFunctions::~HelperFunctions() {
	// TODO Auto-generated destructor stub
}

void HelperFunctions::printGrid(Cell grid[], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			Cell c;
			int index = HelperFunctions::getIndex(i, j, cols);
			c = grid[index];
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
}

void HelperFunctions::computeGrid(Cell* grid, int rows, int cols) {

	int size = rows * cols;

	Cell gridTemp[size];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			int infectedCounter = 0;
			// the cells on the edges of the grid won't check for cells outside the grid,
			// this is what the first if statements are for
			//up
			if (i > 0) {				// if it's not the first row
				if (grid[HelperFunctions::getIndex(i - 1, j, cols)].getPerson(0).getHealthState()
						== 'i') {	// and if the cell just above is infected
					infectedCounter++;				// increment the counter
				};
			};
			//right
			if (j < cols - 1) {				// if it's not the last column
				if (grid[HelperFunctions::getIndex(i, j + 1, cols)].getPerson(0).getHealthState()
						== 'i') {		// if the cell to the right is infected
					infectedCounter++;
				};
			}
			//down
			if (i < rows - 1) {				// if it's not the last row
				if (grid[HelperFunctions::getIndex(i + 1, j, cols)].getPerson(0).getHealthState()
						== 'i') {		// if the cell just below is infected
					infectedCounter++;
				};
			};
			//left
			if (j > 0) { // if it's not the first column
				if (grid[HelperFunctions::getIndex(i, j - 1, cols)].getPerson(0).getHealthState()
						== 'i') { // if the cell to the left is infected
					infectedCounter++;
				};
			};
			char personState;
			char currentState =
					grid[HelperFunctions::getIndex(i, j, cols)].people.at(0).healthState;
			if (infectedCounter > 1) {
				personState = 'i';
			} else {
				personState = currentState;
			}

			Person citizen(personState);
			Cell oneCell;
			oneCell.addPeople(citizen);

			gridTemp[HelperFunctions::getIndex(i, j, cols)] = oneCell;
		}
	}

	for (int i = 0; i < size; i++) {
		grid[i] = gridTemp[i];
	}

}

void HelperFunctions::saveGridToFile(Cell* grid, int rows, int cols,
		string file) {
	ofstream outFile(file.c_str(), ios::out); // creating file object

	if (!outFile) {
		cerr << "File could not be opened" << endl << endl;
	}

	int size = rows * cols;
	outFile << rows << endl;
	outFile << cols << endl;
	for (int i = 0; i < size; i++) {
		int vectorSize = grid[i].people.size();
		outFile << vectorSize << endl;
		for (int j = 0; j < vectorSize; j++) {

			outFile << grid[i].people.at(j).healthState << endl;
			//std::ostream_iterator<std::string> output_iterator(outFile, "\n");
			//std::copy(grid[i].people.begin(), grid[i].people.end(), output_iterator);
		}		 // end of inner for loop

	}		 // end of outer for loop

}		 // end of method

void HelperFunctions::loadGridFromFile(Cell* grid, string file) {
	string line;
	ifstream inFile(file.c_str());
	//ifstream inFile ("001.aut");
	int rows, cols;
	if (inFile.is_open()) {
		inFile >> rows;
		inFile >> cols;
		int size = rows * cols;
		for (int i = 0; i < size; i++) {
			int vectorSize;
			inFile >> vectorSize;
			for (int j = 0; j < vectorSize; j++) {
				inFile >> grid[i].people.at(j).healthState;
			}
		}
		inFile.close();
	}		 // end of if file is open
	else
		cout << "Unable to open file" << endl << endl;
}

int HelperFunctions::getIndex(int r, int c, int cols) {
	int i;
	i = r * cols + c;
	//to translate position from 2D to 1D we need row index, column index and the number of columns of the 2D array
	return i;
}
//
