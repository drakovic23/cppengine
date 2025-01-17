#include <chrono>
#include "BarData.h"

BarData::BarData(double open, double high, double low, double close, long vol, std::chrono::system_clock::time_point date)
	{
		this->open = open;
		this->high = high;
		this->low = low;
		this->close = close;
		this->volume = vol;
		this->dateTest = date;
	}
