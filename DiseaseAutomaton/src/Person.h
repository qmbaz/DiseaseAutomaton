/*
 * Person.h
 *
 *  Jakub Suchecki
 *  B00045505
 *  year 2014
 */

#ifndef PERSON_H_
#define PERSON_H_

class Person {
public:
	Person();
	Person(char);
	Person(char,int);
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
