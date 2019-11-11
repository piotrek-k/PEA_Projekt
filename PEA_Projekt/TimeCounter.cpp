#include "TimeCounter.h"
#include <windows.h>
#include <iostream>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

TimeCounter::TimeCounter()
{
}


TimeCounter::~TimeCounter()
{
}

void TimeCounter::ResetCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;
	this->sumOfTimes = 0.0;
	this->numberOfMeasurements = 0;
}

void TimeCounter::EndSingleMeasurement()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);

	this->numberOfMeasurements++;
	this->sumOfTimes += double(li.QuadPart - CounterStart) / PCFreq;
}

void TimeCounter::StartNextMeasurement()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);

	CounterStart = li.QuadPart;
}

double TimeCounter::Summarize()
{
	return this->sumOfTimes / (double)this->numberOfMeasurements;
}