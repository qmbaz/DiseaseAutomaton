/*
 * Cell.cpp
 *
 *  Jakub Suchecki
 *  B00045505
 *  year 2014
 */

#include "Cell.h"


Cell::Cell() {
	// TODO Auto-generated constructor stub

}

Cell::~Cell() {
	// TODO Auto-generated destructor stub
}

void Cell::addPeople(Person person){
	people.push_back(person);
}

int Cell::getNumberOfPeopleInACell(){
	return people.size();
}

Person Cell::getPerson(int index){
	Person ret;
	ret = people.at(index);
	return ret;
}
//
