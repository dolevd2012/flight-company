#pragma once
#include <iostream>
using namespace std;
#pragma warning (disable: 4996)
#ifndef __FLIGHTCOMPANY_H
#define __FLIGHTCOMPANY_H
#include "Flight.h"
#include "PlaneCrewFactory.h"
using namespace std;

class CFlightCompany
{
public:
	CFlightCompany(const char* companyName);
	CFlightCompany(const CFlightCompany& other);
	CFlightCompany(const char* fileName, int num);
	~CFlightCompany();
	char* getCompanyName() const;
	void SetName(const char* newName);
	void Print(ostream &output);
	bool AddCrewMember(CCrewMember& crewMember);
	bool AddPlane(CPlane& plane);
	bool AddFlight(const CFlight& flight);
	CFlightCompany operator+(const CPlane& plane);
	CFlight* GetFlightByNum(const int num);
	CCrewMember* GetCrewMember(const int num);
	int GetCrewCount() const;
	int GetPlaneCount() const;
	int GetFlightsCount() const;
	void CrewGetPresent();
	void PilotsToSimulator();
	void CrewGetUniform();
	int GetCargoCount();
	void AddCrewToFlight(const int flightNum, const int crewNum);
	CPlane& operator[](int index);
	void SaveToFile(const char* newName);

private:
	CCrewMember** crewMembers;
	CPlane** planes;
	CFlight** flights;
	int currentFlightsSize;
	int currentCrewsSize;
	int currentPlanesSize;
	char* companyName;
};


#endif // !__FLIGHTCOMPANY_H
