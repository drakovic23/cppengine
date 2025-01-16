#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <ctime>
#include <iomanip>

class BarData{
public:
	double open;
	double high;
	double low;
	double close;
	long volume;
	const unsigned char* date;

	BarData(double open, double high, double low, double close, long vol, const unsigned char* date)
	{
		this->open = open;
		this->high = high;
		this->low = low;
		this->close = close;
		this->volume = vol;
		this->date = date;
	}
};

class IStrategy{
	virtual void onBar (const BarData& bar);
	virtual bool shouldEnterTrade() const = 0;
	virtual bool shouldExitTrade() const = 0;
};

class SqliteHelper{
private:
	sqlite3* db_ = nullptr;
	char* errMsg = nullptr;
public:
	//Used to establish a connection to the db file
	explicit SqliteHelper(const std::string fileName)
	{
		int rc = sqlite3_open(fileName.c_str(), &db_);
		if(rc != SQLITE_OK)
		{
			std::cerr << "Cannot open database: " << sqlite3_errmsg(db_) << std::endl;
			sqlite3_close(db_);
		}
	}

	~SqliteHelper()
	{
		if(db_)
			sqlite3_close(db_);
	}

	sqlite3* getDb() const
	{
		return db_;
	}

};

class OhlcMapper{
public:
	//This is a callback function used to map our OHLC data to our BarData class
	//Returns an empty Vector on error
	std::vector<BarData> mapOhlcData(SqliteHelper& sqliteHelper)
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
				
			//TODO: Review if this is optimal
			const unsigned char* dateText = sqlite3_column_text(stmt, 5);
			if(dateText)
			{
				dateText = reinterpret_cast<const unsigned char*>(dateText);
			}
			else
			{
				//TODO: Adjust this later
				dateText = nullptr;
			}
			
			BarData bar(open,high,low,close,volume,dateText);
			bars.push_back(bar);
		}
		
		sqlite3_finalize(stmt);

		return bars;
	}
};

int main()
{
	SqliteHelper db("/home/deni/fin/ingest/data-test.db");

	OhlcMapper mapper;


	std::vector<BarData> bars = mapper.mapOhlcData(db);

	for(const auto &bar : bars){
		std::cout << "Open : " << bar.open << std::endl;
	}
	return 0;
}
