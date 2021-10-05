#pragma warning (disable: 4996)
#include "Address.h"
#include <iostream>
using namespace std;

CAddress::CAddress(int houseNum, const char* street, const char* city)
{
	if (street != NULL)
	{
		this->street = new char[strlen(street) + 1];
		strcpy(this->street, street);
	}
	if (city != NULL)
	{
		this->city = new char[strlen(city) + 1];
		strcpy(this->city, city);
	}
	this->houseNum = houseNum;
}
CAddress::CAddress(ifstream& inFile)
{
	inFile >> this->houseNum;
	char street[10];
	char city[10];
	inFile >> street;
	inFile >> city;
	this->street = strdup(street);
	this->city = strdup(city);
}
void CAddress::UpdateAddress(const char* city, const char* street, int houseNum)
{
	delete(this->street);
	this->street = new char[strlen(street) + 1];
	strcpy(this->street, street);
	delete(this->city);
	this->city = new char[strlen(city) + 1];
	strcpy(this->city, city);
	this->houseNum = houseNum;
}
CAddress CAddress::GetCurrentAddress() const
{
	return *this;
}
ostream& operator<<(ostream& os, const CAddress& obj)
{
	if (&obj == NULL)
	{
		return os;
	}
	os << " Home " << obj.street << " " << obj.houseNum << " " << obj.city;
	return os;
}
istream& operator>>(istream& in, CAddress& obj)
{
	cout << "Please enter house number street name and city name:" << endl;
	char* tempStreet = new char[25];
	char* tempCity = new char[25];
	in >> obj.houseNum >> tempStreet >> tempCity;
	obj.street = new char[strlen(tempStreet) + 1];
	strcpy(obj.street, tempStreet);
	obj.city = new char[strlen(tempCity) + 1];
	strcpy(obj.city, tempCity);
	delete[]tempStreet;
	delete[]tempCity;
	return in;
}
bool CAddress::operator==(const CAddress& other) const
{
	if ((strcmp(this->getCity(), other.getCity()) != 0) || (this->getHouseNum() != other.getHouseNum()) ||
		(strcmp(this->getStreet(), other.getStreet()) != 0))
	{
		return false;
	}
	return true;
}
bool CAddress::operator!=(const CAddress& other) const
{
	return !(*this == other);
}

char* CAddress::getCity() const
{
	return city;
}
char* CAddress::getStreet() const
{
	return street;
}
int CAddress::getHouseNum() const
{
	return houseNum;
}
CAddress::~CAddress()
{
	delete []city;
	delete []street;
}