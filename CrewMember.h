#pragma once
#include <iostream>
using namespace std;
#ifndef __CREWMEMBER_H
#define __CREWMEMBER_H
#include<string.h>
#include <fstream>
#include "FlightCompException.h"
class CCrewMember
{
public:
	CCrewMember(const char* name, int airTime = 0);
	CCrewMember(const CCrewMember& other);
	CCrewMember(ifstream& in);
	virtual ~CCrewMember();
	bool UpdateMinutes(int addAirTime);
	char* getName() const;
	void SetName(char* name);
	int getAirTime() const;
	void setAirTime(int airTime);
	virtual void toOs(ostream& os) const = 0;
	virtual void givePresent() const {};
	virtual void PilotsToSimulator() const {};
	virtual void CrewGetUniform() const {};
	void Print(ostream &output);
	bool operator+=(int newVal);
	bool  operator==(const CCrewMember& other) const;
	virtual void SaveToFile(ofstream& toFile) const = 0;

private:
	char* name;
	int airTime;
};


#endif //__CREWMEMBER_H