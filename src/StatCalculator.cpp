#include <vector>

#include "BarData.h"
#include "StatCalculator.h"

std::vector<double> StatCalculator::calculateReturns(std::vector<BarData> barData)
{
	std::vector<double> returns{};
	for(int i = 1;i < barData.size();i++)
	{
		double ret = (barData[i].close - barData[i-1].close)
			/ barData[i-1].close;

		returns.push_back(ret);
	}

	return returns;
}

