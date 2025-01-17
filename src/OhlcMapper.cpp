#include <iostream>
#include <chrono>

#include "../include/OhlcMapper.h"
#include "../include/SqliteHelper.h"
#include "../include/BarData.h"

std::tm OhlcMapper::parseDateTime(const std::string& dateTimeStr)
{

	std::tm tm = {};
	std::istringstream iss(dateTimeStr);

	iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

	if(iss.fail())
	{
		std::cerr << "Parsing date time has failed, ensure proper format" << std::endl;
	}

	return tm;

}

//This is a callback function used to map our OHLC data to our BarData class
//Returns an empty Vector on error
std::vector<BarData> OhlcMapper::mapOhlcData(SqliteHelper& sqliteHelper)
{
	std::vector<BarData> bars; //BARS FOR DAYS
	const char* selectSQL = "SELECT open, high, low, close, volume, date FROM Ohlc ORDER BY date ASC;";
	
	sqlite3_stmt* stmt = nullptr;
	int rc = sqlite3_prepare_v2(sqliteHelper.getDb(), selectSQL, -1, &stmt, nullptr);
	if(rc != SQLITE_OK)
	{
		std::cerr << "Error preparing statement: " << sqlite3_errmsg(sqliteHelper.getDb()) << std::endl;			
			return bars; //Returns empty vector on error
	}
	
	while((rc = sqlite3_step(stmt)) == SQLITE_ROW)
	{
		double open = sqlite3_column_double(stmt, 0); 
		double high = sqlite3_column_double(stmt, 1); 
		double low = sqlite3_column_double(stmt, 2); 
		double close = sqlite3_column_double(stmt, 3); 
		long volume = sqlite3_column_int64(stmt, 4);

		// Since SQL orders our data, we may not need to actually care about the date type
		const unsigned char* dateText = sqlite3_column_text(stmt, 5);
		std::tm tm{};
		if(dateText)
		{
			//dateText = reinterpret_cast<const unsigned char*>(dateText);
			const char* dateCstr = reinterpret_cast<const char*>(dateText);
			tm = parseDateTime(dateCstr);
		}
		else
		{
			//TODO: Adjust this later
			dateText = nullptr;
		}
		
		std::time_t t = std::mktime(&tm);
		std::chrono::system_clock::time_point tp = std::chrono::system_clock::from_time_t(t);
		BarData bar(open,high,low,close,volume, tp);
		bars.push_back(bar);
	}
		
	sqlite3_finalize(stmt);

	return bars;
}
