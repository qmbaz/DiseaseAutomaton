/*
 * Person.cpp
 *
 *  Jakub Suchecki
 *  B00045505
 *  year 2014
 */

#include "Person.h"

Person::Person() {
	// TODO Auto-generated constructor stub
	healthState = 's';
	timeTillRecovered = -1;
}

Person::Person(char healthStateParam) {
	healthState = healthStateParam;
	timeTillRecovered = -1;

}

Person::Person(char healthStateParam, int timeTill) {
	healthState = healthStateParam;
	timeTillRecovered = timeTill;

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
// add comment
