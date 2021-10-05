#pragma warning (disable: 4996)
#include "CrewMember.h"
#include <iostream>
using namespace std;

CCrewMember::CCrewMember(const char* name, int airTime)
{	
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->airTime = airTime;
}
CCrewMember::CCrewMember(const CCrewMember& other) 
{
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);
	this->airTime = other.airTime;

}
CCrewMember::CCrewMember(ifstream& in)
{
	char name[10];
	in >> name;
	this->name = strdup(name);
	in >> this->airTime;
}
CCrewMember::~CCrewMember()
{	
	delete[]name;
}
void CCrewMember::SetName(char* name)
{
	delete this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}
void CCrewMember::setAirTime(int airTime)
{
	this->airTime = airTime;
}
bool CCrewMember::UpdateMinutes(int add)
{
	if (add < 0)
	{
		return false;
	}
	else 
	{
		this->airTime = getAirTime() + add;
		return true;
	}
}
bool  CCrewMember::operator==(const CCrewMember& other) const
{
	if (strcmp(this->getName(),other.getName()) == 0)
	{
		return true;
	}
	return false;
	
}
bool CCrewMember::operator+=(int newVal)
{
	if (newVal >= 0)
	{
		this->airTime += newVal;
		return true;
	}
	throw CCompStringException("can't add negative air time to crew member");
}
void CCrewMember::Print(ostream &output)
{
	output << typeid(*this).name() + 7 << " ";
	this->toOs(output);
}
char* CCrewMember::getName() const
{
	return name;
}
int CCrewMember::getAirTime() const
{
	return airTime;
}