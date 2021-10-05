#pragma once
#ifndef __CFLOGHTCOMPEXCEPTION_H_
#define __CFLOGHTCOMPEXCEPTION_H_
#include <iostream>
using namespace std;

class CFlightCompException
{
public:
	virtual void Show() const = 0 {};
};

class CCompStringException :CFlightCompException
{
private:
	const char* error;
public:
	CCompStringException(const char* myError) :error(myError) {};
	virtual void Show()const override
	{
		cout << error << endl;
	}
};
class CCompLimitException :CFlightCompException
{
private:
	int max;
public:
	CCompLimitException(int max) : max(max) {};
	virtual void Show()const override
	{
		cout << "PROBLEM!! index must be between 0 - " << max << endl;
	}

};
class CCompFileException :CFlightCompException
{
public:
	virtual void Show() const override
	{
		cout << "Problem with file" << endl;
	}
};

#endif
