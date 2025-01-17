#pragma once

#include <string>
#include <SqliteHelper.h>
#include <BarData.h>


class OhlcMapper{
private:
	std::tm parseDateTime(const std::string& dateTimeStr);

public:
	//This is a callback function used to map our OHLC data to our BarData class
	//Returns an empty Vector on error
	std::vector<BarData> mapOhlcData(SqliteHelper& sqliteHelper);
};
