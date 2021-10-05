#pragma warning (disable: 4996)
#include "Cargo.h"
#include <iostream>
using namespace std;

CCargo::CCargo(int seatsNum, const char* model, float maxWeight, float maxVolume) : CPlane(seatsNum,model)
{
	if (maxWeight < 0)
		throw CCompStringException("Max Weight cant be lower than 0 !");
	if (maxVolume < 0)
		throw CCompStringException("Max Volume cant be lower than 0 !");
	this->maxWeight = maxWeight;
	this->maxVolume = maxVolume;
}
CCargo::CCargo(CCargo& other) : CPlane(other)
{
	this->maxWeight = other.maxWeight;
	this->currentWeight = other.currentWeight;
	this->maxVolume = other.maxVolume;
	this->currentVolume = other.currentVolume;
}
CCargo::CCargo(ifstream& inFile) : CPlane(inFile,-1)
{
	inFile >> this->maxVolume;
	inFile >> maxWeight;
	inFile >> currentVolume;
	inFile >> currentWeight;
}
void CCargo::toOs(ostream& os) const
{
	os << typeid(*this).name() + 7 << " M_vol " << this->maxVolume << " M_Kg " << this->maxWeight << " C_vol " << this->currentVolume << " C_Kg "  << this->currentWeight <<endl;
}
bool CCargo::Load(float weight, float volume)
{
	if (weight + currentWeight > maxWeight || volume + currentVolume > maxVolume)
	{
		return false;
	}
	currentWeight += weight;
	currentVolume += volume;
	return true;
}
void CCargo::TakeOff(int flightTimeInMinutes)
{
	cout << "Need to add " << flightTimeInMinutes << " to my log book" << endl;
}
CPlane& CCargo::getPlane()
{
	return *this;
}
void CCargo::SaveToFile(ofstream& toFile) const
{
	toFile << 1 << " " << getId() << " " << getModel() << " " << getSeatsNum() << endl;
	toFile << maxVolume << " " << maxWeight << " " << currentVolume << " " << currentWeight << endl;
}