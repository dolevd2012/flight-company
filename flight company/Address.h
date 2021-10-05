#pragma once
#include <iostream>
#include <fstream>
using namespace std;
#ifndef __ADDRESS_H
#define __ADDRESS_H

class CAddress
{
private:
	char* city;
	char* street;
	int houseNum;

public:
	CAddress(int houseNum,const char* street,const char* city = "Tel Aviv");
	CAddress(ifstream& inFile);
	~CAddress();
	char* getCity() const;
	char* getStreet() const;
	int getHouseNum() const;
	void UpdateAddress(const char* city,const char* strret, int houseNum);
	CAddress GetCurrentAddress() const;
	friend ostream& operator<<(ostream& os, const CAddress& obj);
	friend istream& operator>>(istream& in, CAddress& obj);
	bool  operator==(const CAddress& other) const;
	bool operator!=(const CAddress& other) const;
};

#endif // __ADDRESS_H