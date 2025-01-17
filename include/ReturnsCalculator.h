#pragma once

#include <vector>

#include "BarData.h"
#include "StatAccumulator.h"

class ReturnsCalculator
{
public:
	//Calculates returns of the given bar data
	static std::vector<double> calculateReturns(std::vector<BarData> barData);
	//Calculates returns and passes them to the provided accumulator to crunch stats
	static void calculateReturns(std::vector<BarData> barData, StatAccumulator& accumulator); 

};
