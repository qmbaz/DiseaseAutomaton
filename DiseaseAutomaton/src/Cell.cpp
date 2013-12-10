/*
 * Cell.cpp
 *
 *  Created on: 1 Dec 2013
 *      Author: kuba
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
