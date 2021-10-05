#pragma warning (disable: 4996)
#include "FlightInfo.h"
#include <iostream>
using namespace std;


CFlightInfo::CFlightInfo(const char* destination, int flightNumber, int flightTimeInMinutes, int distance)
{
	if (flightNumber < 0)
		throw CCompStringException("flightNumber cant be lower than 0 !");
	this->flightNumber = flightNumber;
	if(strlen(destination) > 10)
		throw CCompStringException("Destination string is to long (max is 10 characters)");
	SetDest(destination);
	this->flightTimeInMinutes = flightTimeInMinutes;
	if (flightTimeInMinutes < 0)
		throw CCompStringException("flightTimeInMinutes cant be lower than 0 !");
	this->distance = distance;
	if (distance < 0)
		throw CCompStringException("distance cant be lower than 0 !");
}
CFlightInfo::CFlightInfo(const CFlightInfo& other)
{
	this->flightNumber = other.flightNumber;
	if (other.destination != NULL)
	{
		SetDest(other.destination);
	}
	this->flightTimeInMinutes = other.flightTimeInMinutes;
	this->distance = other.distance;
}
CFlightInfo::CFlightInfo(ifstream& inFile)
{
	char delimeter;
	inFile >> this->destination >> delimeter >> this->flightNumber;
	inFile >> this->flightTimeInMinutes >> delimeter >> this->distance;
}
void CFlightInfo::SetDest(const char* dest)
{
	strcpy(this->destination, dest);
}
int CFlightInfo::GetFNum() const
{
	return flightNumber;
}
ostream& operator<<(ostream& os, const CFlightInfo& obj)
{
	os << "Flight Info dest: " << obj.destination << " Number " << obj.flightNumber <<
		" minutes " << obj.flightTimeInMinutes << " KM " << obj.distance << endl;
	return os;
}
bool CFlightInfo::operator!=(const CFlightInfo& other) const
{
	if (*this == other)
	{
		return false;
	}
	return true;
}
int CFlightInfo::getDistance() const
{
	return distance;
}
char* CFlightInfo::getDestination() 
{
	return this->destination;
}
CFlightInfo::operator int() const
{
	return flightTimeInMinutes;
}