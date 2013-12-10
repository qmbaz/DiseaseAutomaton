/*
 * Person.cpp
 *
 *  Created on: 3 Dec 2013
 *      Author: kuba
 */

#include "Person.h"

Person::Person() {
	// TODO Auto-generated constructor stub
	healthState = 's';
}

Person::Person(char healthStateParam) {
	healthState = healthStateParam;

}



// destructor
Person::~Person() {
	// TODO Auto-generated destructor stub
}

char Person::getHealthState(){
	return healthState;
}

void Person::setHealthState(char state){
	healthState = state;
}
