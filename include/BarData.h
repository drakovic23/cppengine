#pragma once
#include <chrono>

class BarData{
public:
	double open;
	double high;
	double low;
	double close;
	long volume;
	const unsigned char* date;
	std::chrono::system_clock::time_point dateTest;


	BarData(double open, double high, double low, double close, long vol, std::chrono::system_clock::time_point date);

};
