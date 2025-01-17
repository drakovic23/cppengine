#pragma once

#include <vector>

class StatAccumulator{
private:
	std::vector<double> returnValues;

public:
	StatAccumulator();
	void setReturns(std::vector<double>& returnValues);
	void test();
};
