#include "SqliteHelper.h"

#include <sqlite3.h>
#include <iostream>

SqliteHelper::SqliteHelper(const std::string fileName)
{
	int rc = sqlite3_open(fileName.c_str(), &db_);
	if(rc != SQLITE_OK)
	{
		std::cerr << "Cannot open database: " << sqlite3_errmsg(db_) << std::endl;
		sqlite3_close(db_);
	}
}

SqliteHelper::~SqliteHelper()
{
	if(db_)
		sqlite3_close(db_);
}

sqlite3* SqliteHelper::getDb() const
{
	return db_;
}
