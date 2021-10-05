#pragma warning (disable: 4996)
#include "Pilot.h"
#include <iostream>
using namespace std;

CPilot::CPilot(const char* name, bool isCaptain, CAddress* address) : CCrewMember(name, 0)
{
	this->address = address;
	this->isCaptain = isCaptain;
}
CPilot::CPilot(CPilot& other) : CCrewMember(other)
{
	this->address = other.address;
	this->isCaptain = other.isCaptain;
}
CPilot  CPilot::operator=(const CPilot& other)
{
	if (this != &other)
	{
		this->SetName(other.getName());
		this->setAirTime(other.getAirTime());
		this->address = other.address;
		this->isCaptain = other.isCaptain;
	}
	return *this;
}
CPilot::CPilot(ifstream& inFile) : CCrewMember(inFile)
{
	int hasAddress;
	inFile >> hasAddress;
	if (hasAddress == 1)
	{
		this->address = new CAddress(inFile);
	}
	inFile >> this->isCaptain;
}
CAddress* CPilot::getAddress() const
{
	return address;
}
void CPilot::toOs(ostream& os) const
{
	os << this->getName() << " minutes " << this->getAirTime() << " " << *this->address << (this->isCaptain == 0 ? " Not a Captain" : " a Captain") << endl;
}
void CPilot::givePresent() const
{
	cout << this->getName() << " thanking the company for receiving the holiday gift" << endl;
}
void CPilot::PilotsToSimulator() const
{
	cout <<"Pilot " << this->getName() << " got the message will come soon"<< endl;
}
void CPilot::CrewGetUniform() const
{
	cout << this->getName() << ": this is the fifth time I get a new uniform, this is a waste of money!" << endl;
}
void CPilot::SaveToFile(ofstream& toFile) const
{
	CAddress* temp = getAddress();
	if(temp == NULL)
		toFile << 1 << " " << this->getName() << " " << this->getAirTime() << 0 << " " << this->isCaptain <<endl;
	else
	{
		toFile << 1 << " " << this->getName() << " " << this->getAirTime() << " " << 1 << " " << temp->getHouseNum();
		toFile << " " << temp->getStreet() << " " << temp->getCity() << " " << this->isCaptain << endl;
	}
		
}