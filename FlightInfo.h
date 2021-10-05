#pragma once
#include <iostream>
#include <fstream>
using namespace std;
#include "FlightCompException.h"
#ifndef __FLIGHTINFO_H
#define __FLIGHTINFO_H
#define MAX 10
class CFlightInfo
{
public:
	CFlightInfo(const char* destination,int flightNumber,int flightTimeInMinutes,int distance);
	CFlightInfo(const CFlightInfo& other);
	CFlightInfo(ifstream& inFile);
	void SetDest(const char* dest);
	bool operator==(const CFlightInfo& other) const { return this->flightNumber == other.flightNumber; }
	int GetFNum() const;
	char* getDestination();
	int getDistance() const;
	friend ostream& operator<<(ostream& os, const CFlightInfo& obj);
	bool operator!=(const CFlightInfo& other) const;
	int getflightTimeInMinutes() { return flightTimeInMinutes; }
	operator int() const;



private:
	int flightNumber;
	char destination[MAX];
	int flightTimeInMinutes;
	int distance;
};



#endif //__FLIGHTINFO_H