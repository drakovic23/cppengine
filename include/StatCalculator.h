#pragma once

#include <vector>

#include "BarData.h"

class StatCalculator
{
public:
	static std::vector<double> calculateReturns(std::vector<BarData> barData);
};
