/*
 * Cell.h
 *
 *  Jakub Suchecki
 *  B00045505
 *  year 2014
 */

#ifndef CELL_H_
#define CELL_H_

#include <vector>
#include "Person.h"

class Cell {
public:
	Cell();
	virtual ~Cell();
	void addPeople(Person);
	int getNumberOfPeopleInACell();
	Person getPerson(int);
//changed from private to public to have it accessible ...
//private:
	std::vector<Person> people;
};

#endif /* CELL_H_ */
//
