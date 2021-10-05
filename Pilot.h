#pragma once
#include <iostream>
using namespace std;
#ifndef __PILOT_H
#define __PILOT_H
#include<string.h>
#include "CrewMember.h"
#include "Address.h"
class CPilot : public CCrewMember
{
private:
	bool isCaptain;
	CAddress* address;
public:
	CPilot(const char* name, bool isCaptain, CAddress* Address = NULL);
	CPilot(CPilot& other);
	~CPilot() { delete address; }
	CPilot(ifstream& inFile);
	virtual void toOs(ostream& os) const override;
	virtual void givePresent() const override;
	virtual void PilotsToSimulator() const override;
	virtual void CrewGetUniform() const override;
	CAddress* getAddress() const ; 
	CPilot  operator=(const CPilot& other);
	void SaveToFile(ofstream& toFile) const override;

};
#endif
