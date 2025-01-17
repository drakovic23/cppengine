#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <ctime>
#include <string>

#include "BarData.h"
#include "SqliteHelper.h"
#include "OhlcMapper.h"
#include "ReturnsCalculator.h"

int main()
{
	SqliteHelper db("/home/deni/fin/ingest/data-test.db");

	OhlcMapper mapper;

	std::vector<BarData> bars = mapper.mapOhlcData(db, "TSLA");
	
	//std::vector<double> dailyReturns = StatCalculator::calculateReturns(bars);
	
	StatAccumulator accumulator{};
	ReturnsCalculator::calculateReturns(bars, accumulator);
	accumulator.test();
	//std::tm tm_struct;
	/*for(const auto &bar : bars){
	
	// Printing date
	std::string s = std::format("{:%Y-%m-%d}", bar.dateTest);
		std::cout << "Date : " << s << std::endl;
	}*/
	return 0;
}
