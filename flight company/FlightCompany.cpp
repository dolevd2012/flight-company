#pragma warning (disable: 4996)
#include "FlightCompany.h"
#include <iostream>
#include <fstream>
#include "Host.h"
#include "Pilot.h"
#include "Cargo.h"
#include "FlightCompException.h"
using namespace std;
#define maxSize 10

CFlightCompany::CFlightCompany(const char* name): currentCrewsSize(0), currentPlanesSize(0) , currentFlightsSize(0)
{
	this->flights = new CFlight*[maxSize];
	this->crewMembers = new CCrewMember*[maxSize];
	this->planes = new CPlane*[maxSize];
	if (name != NULL)
	{
		this->companyName = new char[strlen(name) + 1];
		strcpy(this->companyName, name);
	}
	else
	{
		name = NULL;
	}
}
CFlightCompany::CFlightCompany(const CFlightCompany& other) {
	this->companyName = new char[strlen(other.companyName) + 1];
	strcpy(this->companyName, other.companyName);
	this->currentCrewsSize = other.currentCrewsSize;
	this->currentFlightsSize = other.currentFlightsSize;
	this->currentPlanesSize = other.currentPlanesSize;
	this->flights = other.flights;
	this->planes = other.planes;
	this->crewMembers = other.crewMembers;
}
CFlightCompany::CFlightCompany(const char* fileName, int num) : currentCrewsSize(0), currentPlanesSize(0), currentFlightsSize(0)
{

	char companyName[10];
	ifstream inFile(fileName);
	if (inFile.fail())
	{
		throw CCompFileException();
	}
	inFile >> companyName;
	this->companyName = strdup(companyName);
	inFile >> this->currentCrewsSize;
	this->crewMembers = new CCrewMember*[currentCrewsSize];
	int temp;
	for (int i = 0; i < currentCrewsSize; i++)
	{
		inFile >> temp;
		switch (temp)
		{
		case(0):
		{
			this->crewMembers[i] = new CHost(inFile);
			break;
		}
		case(1):
		{
			this->crewMembers[i] = new CPilot(inFile);
			break;
		}
		default:
			break;
		}

	}
	inFile >> currentPlanesSize;
	this->planes = new CPlane*[currentPlanesSize];
	for (int i = 0; i < currentPlanesSize; i++)
	{
		inFile >> temp;
		switch (temp)
		{
		case(0):
		{
			//Passing i to read the counter once when its the first plane!
			this->planes[i] = new CPlane(inFile,i);
			break;
		}
		case(1):
		{
			this->planes[i] = new CCargo(inFile);
			break;
		}
		default:
			break;
		}
	}
	inFile >> this->currentFlightsSize;
	this->flights = new CFlight*[currentFlightsSize];
	for (int i = 0; i < currentFlightsSize; i++)
	{
		this->flights[i] = new CFlight(inFile);
	}
}
void CFlightCompany::Print(ostream &output)
{
	if (companyName == "")
		throw CCompStringException("FlightCompany name cant have an empty string");
	output << "Flight company: " << companyName << endl;
	output << "There are "<< currentCrewsSize << " Crew members:" << endl;
	for (int i = 0; i < currentCrewsSize; i++)
	{
		crewMembers[i]->Print(cout);
	}
	cout << "There are " << currentPlanesSize << " Planes:" << endl;
	for (int i = 0; i < currentPlanesSize; i++)
	{
		output << *planes[i];
	}
	cout << "There are " << currentFlightsSize << " Flights:" << endl;
	for (int i = 0; i < currentFlightsSize; i++)
	{
		output << *flights[i];
	}

}
void CFlightCompany::SetName(const char* newName)
{
	delete[] this->companyName;
	this->companyName = new char[strlen(newName) + 1];
	strcpy(this->companyName, newName);
}
char* CFlightCompany::getCompanyName() const
{
	return companyName;
}
int CFlightCompany::GetCrewCount() const
{
	return currentCrewsSize;
}
int CFlightCompany::GetPlaneCount() const
{
	return currentPlanesSize;
}
int CFlightCompany::GetFlightsCount() const
{
	return currentFlightsSize;
}
bool CFlightCompany::AddFlight(const CFlight& flight)
{
	for (int i = 0; i < currentFlightsSize; i++)
	{
		if (flights[i]->compareFlights(flight) == true)
		{
			return false;
		}
	}
	flights[currentFlightsSize] = new CFlight(flight);
	currentFlightsSize++;
	return true;

}
bool CFlightCompany::AddCrewMember(CCrewMember& crewMember)
{
	for (int i = 0; i < currentCrewsSize; i++)
	{
		if (*crewMembers[i] == crewMember)
		{
			return false;
		}
	}
	if (strcmp(typeid(crewMember).name() + 7, typeid(CHost).name() + 7) == 0)
	{
		CHost* temp = dynamic_cast<CHost*>(&crewMember);
		crewMembers[currentCrewsSize] = new CHost(*temp);
	}
	if (strcmp(typeid(crewMember).name() + 7, typeid(CPilot).name() + 7) == 0)
	{
		CPilot* temp = dynamic_cast<CPilot*>(&crewMember);
		crewMembers[currentCrewsSize] = new CPilot(*temp);
	}
	currentCrewsSize++;
	return true;
}
CPlane& CFlightCompany::operator[](int index)
{

	if (index < currentPlanesSize && index > -1)
		return planes[index]->getPlane();
	throw CCompLimitException(currentPlanesSize);
}
bool CFlightCompany::AddPlane(CPlane& plane)
{
	for (int i = 0; i < currentPlanesSize; i++)
	{
		if (*this->planes[i] == plane)
		{
			return false;
		}
	}
	if (currentPlanesSize < maxSize)
	{
		if (strcmp(typeid(plane).name() + 7, typeid(CCargo).name() + 7) == 0)
		{
			CCargo* temp = dynamic_cast<CCargo*>(&plane);
			this->planes[currentPlanesSize] = new CCargo(*temp);
			this->currentPlanesSize++;
			return true;
		}
		this->planes[currentPlanesSize] = new CPlane(plane);
		this->currentPlanesSize++;
		return true;
	}
	return false;
}
CFlight* CFlightCompany::GetFlightByNum(const int num)
{
	for (int i = 0; i < currentFlightsSize; i++)
	{
		if (flights[i]->GetFlightInfo().GetFNum() == num)
		{
			return flights[i];
		}
	}
}
CCrewMember* CFlightCompany::GetCrewMember(const int num)
{
	if (num <= currentCrewsSize && num > -1)
	{
		return crewMembers[num];
	}
	throw CCompLimitException(currentCrewsSize);
}
void CFlightCompany::AddCrewToFlight(const int flightNum, const int crewNum)
{
	CFlight* tempFlight = GetFlightByNum(flightNum);
	CCrewMember* tempCrew = GetCrewMember(crewNum);
	*tempFlight = *tempFlight + tempCrew;
}
void CFlightCompany::CrewGetPresent()
{
	for (int i = 0; i < currentCrewsSize; i++)
	{
		this->crewMembers[i]->givePresent();
	}
}
void CFlightCompany::PilotsToSimulator()
{
	for (int i = 0; i < currentCrewsSize; i++)
	{
		this->crewMembers[i]->PilotsToSimulator();
	}
}
void CFlightCompany::CrewGetUniform()
{
	for (int i = 0; i < currentCrewsSize; i++)
	{
		this->crewMembers[i]->CrewGetUniform();
	}
}
int CFlightCompany::GetCargoCount()
{
	int count = 0;
	for (int i = 0; i < currentPlanesSize; i++)
	{
		if (strcmp(typeid(*this->planes[i]).name() + 7, typeid(CCargo).name() + 7) == 0)
		{
			count++;
		}
	}
	return count;
}
CFlightCompany CFlightCompany::operator+(const CPlane& plane)
{
	for (int i = 0; i < currentPlanesSize; i++)
	{
		if (*planes[i] == (plane))
		{
			cout << "plane already exists " << endl;
			return *this;
		}
	}
	this->planes[currentPlanesSize] = new CPlane(plane.getSeatsNum(), plane.getModel());
	this->currentPlanesSize++;
	return *this;
}
void CFlightCompany::SaveToFile(const char* newName)
{
	ofstream toFile(newName);
	toFile << this->companyName << endl;
	toFile << this->GetCrewCount() << endl;
	for (int i = 0; i < GetCrewCount(); i++)
	{
		this->crewMembers[i]->SaveToFile(toFile);
	}
	toFile << this->GetPlaneCount() << endl;
	for (int i = 0; i < GetPlaneCount(); i++)
	{
		this->planes[i]->SaveToFile(toFile);
	}
	toFile << this->GetFlightsCount() << endl;
	for (int i = 0; i < GetFlightsCount(); i++)
	{
		this->flights[i]->SaveToFile(toFile);
	}



}


CFlightCompany::~CFlightCompany()
{
	delete[]companyName;
	for (int i = 0; i < currentFlightsSize; i++)
	{
		delete flights[i];
	}
	for (int i = 0; i < currentCrewsSize; i++)
	{
		delete crewMembers[i];
	}
	delete[]crewMembers;
	delete[]planes;

}