#include <vector>
#include <iostream>

#include "StatAccumulator.h"

StatAccumulator::StatAccumulator()
{
}
//TODO: Since our vector in ReturnsCalcultor goes out of scope
void StatAccumulator::setReturns(std::vector<double>& returnValues)
{
	this->returnValues = returnValues;
}

void StatAccumulator::test()
{
	for(int i = 0;i < returnValues.size();i++)
	{
		std::cout << returnValues[i] << std::endl;
	}
}


