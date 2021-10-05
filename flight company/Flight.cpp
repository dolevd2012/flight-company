#pragma warning (disable: 4996)
#include <iostream>
using namespace std;
#include "Flight.h"
#include "Host.h"
#include "Pilot.h"
#include "Cargo.h"
#define MAXSIZE 10

CFlight::CFlight(const CFlightInfo& flightInfo,CPlane* plane):flightInfo(flightInfo)
{
	this->SetPlane(plane);
	this->maxSize = MAXSIZE;
	this->crewMembers = new CCrewMember*[maxSize];
	this->currentCrewSize = 0;

}
CFlight::CFlight(const CFlight& other) : flightInfo(other.flightInfo)
{
	this->maxSize = other.maxSize;
	this->crewMembers = other.crewMembers;
	this->currentCrewSize = other.currentCrewSize;
	this->SetPlane(plane);
}
CFlight::CFlight(ifstream& inFile): flightInfo(inFile)
{
	int hasPlane = 0;
	int planeId;
	int temp;
	inFile >> hasPlane;
	if (hasPlane == 1)
	{
		inFile >> planeId;
		this->plane = NULL;
	}
	inFile >> this->currentCrewSize;
	this->crewMembers = new CCrewMember*[maxSize];
	for (int i = 0; i < currentCrewSize; i++)
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

}
CPlane* CFlight::GetPlane() const
{
	return this->plane;
}
void CFlight::SetPlane(CPlane* plane)
{
	this->plane = plane;
}
CFlightInfo CFlight::GetFlightInfo()
{
	return this->flightInfo;
}
ostream& operator<<(ostream& os,const CFlight& obj)
{
	cout << obj.flightInfo;
	if (obj.GetPlane() == NULL)
	{
		cout << "No plane assign yet " << endl;
	}
	else
	{
		cout << *obj.plane;
	}
	cout << "There are " << obj.currentCrewSize << " crew memebers in flight: " << endl;
	for (int i = 0; i < obj.currentCrewSize; i++)
	{
		obj.crewMembers[i]->Print(cout);
	}
	return os;
}
bool CFlight::compareFlights(const CFlight& other) const
{
	if (this->flightInfo != other.flightInfo)
	{
		return false;
	}
	return true;
}
CFlight& CFlight::operator+(CCrewMember* crewMember)
{
	for (int i = 0; i < this->currentCrewSize; i++)
	{
		if (strcmp((*this->crewMembers[i]).getName(), crewMember->getName()) == 0)
		{
			cout << "Member already exists " << endl;
			return *this;
		}
	}
	if (strcmp(typeid(*crewMember).name() + 7, typeid(CHost).name() + 7) == 0)
	{
		CHost* temp1 = dynamic_cast<CHost*>(crewMember);
		this->crewMembers[currentCrewSize] = temp1;
		this->currentCrewSize++;
	}
	if (strcmp(typeid(*crewMember).name() + 7, typeid(CPilot).name() + 7) == 0)
	{
		CPilot* temp1 = dynamic_cast<CPilot*>(crewMember);
		crewMembers[currentCrewSize] = temp1;
		this->currentCrewSize++;
	}
	return *this;
}
bool CFlight::TakeOff()
{
	if (plane == NULL)
	{
		throw CCompStringException("No plane found on this flight!");
	}
	CFlightInfo temp = GetFlightInfo();
	if (strcmp(typeid(*plane).name() + 7, typeid(CCargo).name() + 7) == 0)
	{	
		int countPilots = 0;
		for (int i = 0; i < currentCrewSize; i++)
		{
			if (strcmp(typeid(*crewMembers[i]).name() + 7, typeid(CPilot).name() + 7) == 0)
			{
				countPilots++;
			}
		}
		if (countPilots == 1)
		{
			for (int i = 0; i < currentCrewSize; i++)
			{
				*crewMembers[i] += temp.getflightTimeInMinutes();
			}
			((CCargo*)this->plane)->TakeOff(temp.getflightTimeInMinutes());
			return true;
		}
		else 
		{
			throw CCompStringException("Only 1 pilot is needed for Cargo plane!");
		}
	}
	if (strcmp(typeid(*plane).name() + 7, typeid(CPlane).name() + 7) == 0)
	{
		int countPilots = 0;
		int countSeniorAttdendant = 0;
		for (int i = 0; i < currentCrewSize; i++)
		{
			if (strcmp(typeid(*crewMembers[i]).name() + 7, typeid(CPilot).name() + 7) == 0)
			{
				countPilots++;
			}
			if (strcmp(typeid(*crewMembers[i]).name() + 7, typeid(CHost).name() + 7) == 0)
			{
				CHost* temp = dynamic_cast<CHost*>(crewMembers[i]);
				
				if (temp->getMyStatus() == 1)
				{
					countSeniorAttdendant++;
				}
			}
		}
		if (countPilots == 1 && countSeniorAttdendant == 1)
		{
			for (int i = 0; i < currentCrewSize; i++)
			{
				*crewMembers[i] += temp.getflightTimeInMinutes();
			}
			return true;
		}
		else
		{
			throw CCompStringException("Problem found in plane take off!");
		}
	}
}
void CFlight::SaveToFile(ofstream& toFile)
{
	if (this->GetPlane() != NULL)
	{
		toFile << flightInfo.getDestination() << " " << flightInfo.GetFNum() << " " << flightInfo.getflightTimeInMinutes() << " " << flightInfo.getDistance() << this->GetPlane()->getId() << endl;
		for (int i = 0; i < currentCrewSize; i++)
		{
			crewMembers[i]->SaveToFile(toFile);
		}
	}
	else 
	{
		toFile << flightInfo.getDestination() << " " << flightInfo.GetFNum() << " " << flightInfo.getflightTimeInMinutes() << " " << flightInfo.getDistance() << endl;
		for (int i = 0; i < currentCrewSize; i++)
		{
			crewMembers[i]->SaveToFile(toFile);
		}
	}
}

CFlight::~CFlight()
{
	delete[]plane;
}
