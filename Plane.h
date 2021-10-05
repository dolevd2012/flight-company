#pragma once
#include <iostream>
using namespace std;
#ifndef __PLANE_H
#define __PLANE_H
#include <fstream>
#include "FlightCompException.h"
class CPlane
{
public:
	CPlane(int seatsNum, const char* model);
	CPlane(const CPlane& other);
	CPlane(ifstream& inFile,int index);
	virtual ~CPlane();
	int getId()  const;
	char* getModel()  const;
	int getSeatsNum()  const;
	virtual void toOs(ostream& os) const {};
	bool  operator==(const CPlane& other) const;
	virtual CPlane& getPlane();
	friend ostream& operator<<(ostream& os, const CPlane& obj);
	const CPlane&  operator++();
	CPlane&  operator++(int);
	virtual void SaveToFile(ofstream& toFile) const;

private:
	static int counter;
	int id;
	char* model;
	int seatsNum;

};

#endif // __PLANE_H