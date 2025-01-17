#pragma once

#include <sqlite3.h>
#include <string>

class SqliteHelper{
private:
	sqlite3* db_ = nullptr;
	char* errMsg = nullptr;
public:
	//Used to establish a connection to the db file
	explicit SqliteHelper(const std::string fileName);


	~SqliteHelper();

	sqlite3* getDb() const;

};
