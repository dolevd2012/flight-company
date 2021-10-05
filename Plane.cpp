#pragma warning (disable: 4996)
#include "Plane.h"
#include <iostream>
using namespace std;

int CPlane::counter = 100;

CPlane::CPlane(int seatsNum, const char* model)
{
	this->id = counter++;
	if (seatsNum < 0)
		throw CCompStringException("Seats in plane can't be lower than 0 !");
	this->seatsNum = seatsNum;
	if (model != NULL)
	{
		this->model = new char[strlen(model) + 1];
		strcpy(this->model, model);
	}
	else
	{
		this->model = NULL;
	}
}
CPlane::CPlane(const CPlane& other)
{

	this->id = other.id;
	this->seatsNum = other.seatsNum;
	if (other.model != NULL)
	{
		this->model = new char[strlen(other.model) + 1];
		strcpy(this->model, other.model);
	}
	else
	{
		this->model = NULL;
	}
}
CPlane::CPlane(ifstream& inFile,int index)
{
	char tempDegem[10];
	if (index == 0)
	{
		inFile >> this->counter;
	}
	inFile >> this->id;
	inFile >> tempDegem;
	this->model = strdup(tempDegem);
	inFile >> this->seatsNum;
}
CPlane::~CPlane()
{
	delete []model;
}
const CPlane& CPlane::operator++()
{
	this->seatsNum++;
	return *this;
}
CPlane& CPlane::operator++(int)
{
	CPlane temp = *this;
	++*this;
	return temp;
}
ostream& operator<<(ostream& os, const CPlane& obj)
{
	os << "Plane " << obj.id << " degem " << obj.model << " seats " << obj.seatsNum << endl;
	obj.toOs(os);
	return os;
}
CPlane& CPlane::getPlane()
{
	return *this;
}
int CPlane::getId() const
{
	return id;
}
char* CPlane::getModel() const
{
	return model;
}
int CPlane::getSeatsNum() const
{
	return seatsNum;
}
bool  CPlane::operator==(const CPlane& other) const
{
	return this->id == other.getId();
}
void CPlane::SaveToFile(ofstream& toFile) const
{
	toFile << 0 << " " << counter << " " << id << " " << model << " " << seatsNum << endl;
}