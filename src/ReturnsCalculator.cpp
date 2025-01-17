#include <vector>
#include <iostream>
#include "BarData.h"
#include "ReturnsCalculator.h"

std::vector<double> ReturnsCalculator::calculateReturns(std::vector<BarData> barData)
{

	std::vector<double> returns{};
	if(barData.size() < 2)
	{
		std::cerr << "Error: barData in calculateReturns() must be >= 2";
		return returns;
	}

	for(int i = 1;i < barData.size();i++)
	{
		double ret = (barData[i].close - barData[i-1].close)
			/ barData[i-1].close;
		
		returns.push_back(ret);
	}

	//mean = returnSum / barData.size();
	return returns;
}

void ReturnsCalculator::calculateReturns(std::vector<BarData> barData, StatAccumulator& accumulator)
{
	
	std::vector<double> returns{};
	if(barData.size() < 2)
	{
		std::cerr << "Error: barData in calculateReturns() must be >= 2";
		return;
	}

	for(int i = 1;i < barData.size();i++)
	{
		double ret = (barData[i].close - barData[i-1].close)
			/ barData[i-1].close;
		
		returns.push_back(ret);
	}
	

	//TODO: Verify
	accumulator.setReturns(returns);
}
