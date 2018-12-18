#include <ccxx/ccxx.h>

#include <ccxx/cxdatabase_odbc.h>

#include "test_cursor1.hpp"
#include "test_dql1.hpp"

using namespace std;

int fn_interinfo_in_cmd( const std::string & sCommand, const std::map<std::string, std::string> & sParams, const msepoch_t & dtIn, int iSource, int eInType, int iTag)
{
	if (sCommand == "exit")
	{
		CxApplication::exit();
		return TRUE;
	}
	else
	{
		cxPrompt() << "in : " << sCommand;
	}
	return FALSE;
}

void fn_timer1(int)
{
	cxPrompt() << "begin time1:";

	testDql6();
}

void fn_test(int, int, const void *, int, void *, void *)
{
}

int main(int argc,const char * argv[])
{
	cout << "begin test CxDatabase-ODBC : ";

	CxApplication::init(argc, argv);

	string g_sDBSource = "UID=ICS;PWD=ICS;DSN=ics_oracle_dsn";
	string g_sDBType = "Oracle";

//	string g_sDBSource = "UID=root;PWD=123456;DSN=ics_mysql_dsn";
//	string g_sDBType = "MySQL";

//	string g_sDBSource = "DSN=ics_access_dsn";
//	string g_sDBType = "access";


	CxDatabase * pDb = CxDatabaseManager::createDatabase(g_sDBSource, g_sDBType);
	if (pDb == NULL)
	{
		cout << "end test !!!";
		return 0;
	}
	cout << " pDb->openDatabase() : " << pDb->openDatabase();

//	testCursor1();
//	testCursor2();

//    cout << "end test CxDatabase !!!";

	CxInterinfoIn::addObserver(fn_interinfo_in_cmd);

	CxApplication::pushProcessCallBack(fn_test);

	CxTimerManager::startTimer(fn_timer1, 1000);

	return CxApplication::exec();
}