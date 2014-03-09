/*
 * Person.h
 *
 *  Created on: 3 Dec 2013
 *      Author: kuba
 */

#ifndef PERSON_H_
#define PERSON_H_

class Person {
public:
	Person();
	Person(char);
	virtual ~Person();

	char getHealthState();
	void setHealthState(char);

// make healthstate public to have it accessible
//private:
	char healthState;// Susceptible, Infected, Removed/Recovered
	int timeTillRecovered;

};




#endif /* PERSON_H_ */
//
