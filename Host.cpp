#pragma warning (disable: 4996)
#include "Host.h"
#include <iostream>
using namespace std;

const char* statusStr[] = { "Regular", "Super", "Calaelan" };

CHost::CHost(const char* name, status myStatus) : CCrewMember(name,0)
{
	this->myStatus = myStatus;
}
CHost::CHost(const CHost& other) : CCrewMember(other)
{
	this->myStatus = other.myStatus;
}
CHost::CHost(ifstream& in) : CCrewMember(in)
{
	int tempStatus;
	in >> tempStatus;
	this->myStatus = static_cast<status>(tempStatus);
}
CHost  CHost::operator=(const CHost& other)
{
	if (this != &other)
	{
		this->SetName(other.getName());
		this->setAirTime(other.getAirTime());
		this->myStatus = other.myStatus;
	}
	return *this;
}
void CHost::toOs(ostream& os) const
{
	os << statusStr[(int)myStatus] << " " << this->getName() << " minutes " << this->getAirTime() << endl;
}
void CHost::givePresent() const
{
	cout << this->getName() << " thanking the company for receiving the holiday gift" << endl;
	cout << "I was not expecting it" << endl;		
}
void CHost::CrewGetUniform() const
{
	cout << this->getName() << ": I think the new uniform is very nice!" << endl;
}
void CHost::SaveToFile(ofstream& toFile) const
{
	toFile << 0 << " " << this->getName() << " " << this->getAirTime() << " " << myStatus << endl;
}