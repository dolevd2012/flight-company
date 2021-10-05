#pragma once
#include <iostream>
using namespace std;
#ifndef __CCargo_H
#define __CCargo_H
#include<string.h>
#include "Plane.h"
class CCargo : public CPlane
{
private:
	float maxWeight;
	float maxVolume;
	float currentWeight;
	float currentVolume;
public:
	CCargo(int seatsNum, const char* model, float maxWeight, float maxVolume);
	CCargo(CCargo& other);
	CCargo(ifstream& inFile);
	virtual void toOs(ostream& os) const;
	bool Load(float currentWeight, float currentVolume);
	void TakeOff(int flightTimeInMinutes);
	virtual CPlane& getPlane() override;
	virtual void SaveToFile(ofstream& toFile) const override;

};
#endif