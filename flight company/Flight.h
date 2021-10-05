#pragma once
#include <iostream>
using namespace std;
#ifndef __FLIGHT_H
#define __FLIGHT_H
#include "FlightInfo.h"
#include "Plane.h"
#include "CrewMember.h"
class CFlight
{
private:
	CFlightInfo flightInfo;
	CPlane* plane;
	CCrewMember** crewMembers;
	int currentCrewSize;
	int maxSize;

public:
	CFlight(const CFlightInfo& flightInfo, CPlane* plane = NULL);
	CFlight(const CFlight& other);
	CFlight(ifstream& inFile);
	~CFlight();
	friend ostream& operator<<(ostream& os,const CFlight& obj);
	void SetPlane(CPlane* plane);
	CPlane* GetPlane() const;
	CFlightInfo GetFlightInfo();
	bool compareFlights(const CFlight& other) const ;
    CFlight& operator+(CCrewMember* crewMember);
	bool TakeOff();
	void SaveToFile(ofstream& toFile);
};

#endif

