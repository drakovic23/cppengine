#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <format>
#include <string>

#include "../include/BarData.h"
#include "../include/SqliteHelper.h"
#include "../include/OhlcMapper.h"
class IStrategy{
	virtual void onBar (const BarData& bar);
	virtual bool shouldEnterTrade() const = 0;
	virtual bool shouldExitTrade() const = 0;
};


int main()
{
	SqliteHelper db("/home/deni/fin/ingest/data-test.db");

	OhlcMapper mapper;

	std::vector<BarData> bars = mapper.mapOhlcData(db);
	
	std::tm tm_struct;
	for(const auto &bar : bars){
	
	// Printing date
	//std::string s = std::format("{:%Y-%m-%d}", bar.dateTest);
	//	std::cout << "Date : " << s << std::endl;
	}
	return 0;
}
