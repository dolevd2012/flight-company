#pragma warning (disable: 4996)
#include "PlaneCrewFactory.h"
#include <iostream>
using namespace std;

PlaneType CPlaneCrewFactory::GetPlaneType(const CPlane* pPlane)
{
	if (strcmp(typeid(*pPlane).name() + 7, typeid(CPlane).name() + 7) == 0)
		return PlaneType(0);
	if (strcmp(typeid(*pPlane).name() + 7, typeid(CCargo).name() + 7) == 0)
		return PlaneType(1);
}
CrewType CPlaneCrewFactory::GetCrewType(const CCrewMember* pCrew)
{
	if (strcmp(typeid(*pCrew).name() + 7, typeid(CHost).name() + 7) == 0)
		return CrewType(0);
	if (strcmp(typeid(*pCrew).name() + 7, typeid(CPilot).name() + 7) == 0)
		return CrewType(1);
}


void CPlaneCrewFactory::GetCompanyDataFromUser(CFlightCompany& comp)
{
	char answer;
	cout << "Welcome to " << comp.getCompanyName() << " Would you like to a plane or a crew member? (p-plane c-crewmember) ";
	cin >> answer;
	switch (answer)
	{
	case('p'):
	{
		comp.AddPlane(*GetPlaneFromUser());
		break;
	}
	case('c'):
	{
		comp.AddCrewMember(*GetCrewFromUser());
		break;
	}
	default:
		cout << "You chose none !" << endl;
		break;
	}
	

}

CPlane* CPlaneCrewFactory::GetPlaneFromUser()
{
	int planeType;
	int numOfSeats;
	char model[10];
	cout << "Plane: - Enter 1 for regular or 2 for cargo:" << endl;
	cin >> planeType;
	switch (planeType)
	{
		case(1):
		{
			cout << "You chose regular plane!, choose num of seats and model for the plane: ";
			cin >> numOfSeats >> model;
			CPlane* myPlane = new CPlane(numOfSeats, model);
			return myPlane;
			break;
		}
		case(2):
		{
			float maxWeight;
			float maxVolume;
			cout << "You chose cargo plane!, choose num of seats and model for the plane: ";
			cin >> numOfSeats >> model;
			cout << "allmost Done!,now choose max weight and max volume for your plane: ";
			cin >> maxWeight >> maxVolume;
			CPlane* myPlane = new CCargo(numOfSeats, model, maxWeight, maxVolume);
			return myPlane;
			break;
		}
		default:
			return NULL;
			break;
	}
}
CCrewMember* CPlaneCrewFactory::GetCrewFromUser()
{
	int crewType;
	char name[10];
	char status;
	cout << "CrewMember: - Enter 1 for Host or 2 for Pilot:" << endl;
	cin >> crewType;
	switch (crewType)
	{
	case(1): {
		cout << "You chose Host!, choose host name and status(r-regular , s-super c - calcelan): ";
		cin >> name >> status;
		switch (status)
		{
			case('r'):
			{
				CCrewMember* crew = new CHost(name, CHost::eRegular);
				return crew;
				break;
			}
			case('s'):
			{
				CCrewMember* crew = new CHost(name, CHost::eSuper);
				return crew;
				break;
			}
			case('c'):
			{
				CCrewMember* crew = new CHost(name, CHost::eCalcelan);
				return crew;
				break;
			}
			{
			default:
				break;
			}
			break;
		}
	case(2): {
		int captainStatus;
		cout << "You chose Pilot!, choose host name and captain status(0 - no , 1 - yes): ";
		cin >> name >> captainStatus;
		cout << "allmost Done!,would you like to add address? (y-yes , any other letter for no): ";
		cin >> status;
		switch (status)
		{
			case('y'): 
			{
				char city[10];
				char street[10];
				int streetNum;
				cout << "add street number , street and city: ";
				cin >> streetNum >> street >> city;
				CAddress* address = new CAddress(streetNum,street,city);
				CCrewMember* crew = new CPilot(name, captainStatus,address);
				return crew;
				break;
			}
			default:
				CCrewMember* crew = new CPilot(name, captainStatus);
				return crew;
				break;
			}
		}
	default:
		break;
		}
	}

}
CCrewMember* CPlaneCrewFactory::GetCrewMemberFromFile(ifstream& inFile)
{
	int temp;
	inFile >> temp;
	switch (temp)
	{
	case(0):
	{
		CCrewMember* myCrew = new CHost(inFile);
		return myCrew;
	}
	case(1):
	{
		CCrewMember* myCrew = new CPilot(inFile);
		return myCrew;
	}
	default:
		break;
	}
}
CPlane* CPlaneCrewFactory::GetPlaneFromFile(ifstream& inFile)
{
	int temp;
	inFile >> temp;
	switch (temp)
	{
	case(0):
	{
		CPlane* myPlane = new CPlane(inFile,0);
		return myPlane;
	}
	case(1):
	{
		CPlane* myPlane = new CCargo(inFile);
		return myPlane;
	}
	default:
		break;
	}
}