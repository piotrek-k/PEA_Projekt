#pragma once
class TimeCounter
{
	double PCFreq = 0.0;
	__int64 CounterStart = 0;
	double sumOfTimes = 0.0;
	int numberOfMeasurements = 0;
public:
	TimeCounter();
	~TimeCounter();
	void ResetCounter();
	void EndSingleMeasurement();
	void StartNextMeasurement();
	/// <summary>
	/// Calculates time difference
	/// </summary>
	/// <returns>Result in miliseconds</returns>
	double Summarize();
};

