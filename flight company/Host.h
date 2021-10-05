#pragma once
#include <iostream>
using namespace std;
#ifndef __HOST_H
#define __HOST_H
#include<string.h>
#include "CrewMember.h"
class CHost : public CCrewMember
{
public:
	enum status { eRegular , eSuper , eCalcelan };
	CHost(const char* name , status myStatus);
	CHost(const CHost& other);
	CHost(ifstream& in);
	virtual void toOs(ostream& os) const override;
	virtual void givePresent() const override;
	virtual void CrewGetUniform() const override;
	CHost  operator=(const CHost& other) ;
	enum status getMyStatus() { return this->myStatus ; }
	void SaveToFile(ofstream& toFile) const override;

private: 
	status myStatus;
};


#endif