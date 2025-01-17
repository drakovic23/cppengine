#pragma once

#include <vector>

#include "BarData.h"

class StatCalculator
{
public:
	static std::vector<double> calculateDescriptive(std::vector<BarData> barData);
};
