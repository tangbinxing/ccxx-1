
#include <ccxx/ccxx.h>

using namespace std;

CxDatabase::CursorBase * f_oCursor1 = NULL;
CxDatabase::CursorBase * f_oCursor2 = NULL;

void timerCursor1(int iInterval)
{
    static int iIndex = 0;
    ++ iIndex;
    msepoch_t dtNow = CxTime::currentSystemTime();
    CxDatabase * oDb = CxDatabaseManager::getDefaultDb();
    if (oDb == NULL)
    {
        cxPrompt() << "can not open database!";
        return;
    }

    cxPrompt() << "DB has cursor count : " << oDb->cursorGetOnlineAll().size();

    if (f_oCursor1 == NULL)
    {
        string sSql = "select * from ha_appconfig";
        f_oCursor1 = oDb->cursorLoad(sSql, 10);
    }

    if (f_oCursor2 == NULL)
    {
        string sSq2 = "select * from omc_neconfig";
        f_oCursor2 = oDb->cursorLoad(sSq2, 10);
    }

    if (! oDb->cursorIsEnd(f_oCursor1))
    {
        vector<std::vector<std::string> > rows;
        oDb->cursorPut(f_oCursor1, rows);
        if (rows.size() > 0)
        {
            vector<string> row = CxEncoding::utf8ToGb2312(rows[0]);
            cxPrompt() << "cursor1 cursorPut row count : " << rows.size()
                       << " , print line0: ";
            cxPrompt() << row;
        }
    }
    if (oDb->cursorIsEnd(f_oCursor1))
    {
        oDb->cursorClose(f_oCursor1);
        f_oCursor1 = NULL;
    }

    if (! oDb->cursorIsEnd(f_oCursor2))
    {
        vector<std::vector<std::string> > rows;
        oDb->cursorPut(f_oCursor2, rows);
        if (rows.size() > 0)
        {
            vector<string> row = CxEncoding::utf8ToGb2312(rows[0]);
            cxPrompt() << "cursor2 cursorPut row count : " << rows.size()
                       << " , print line0: ";
            cxPrompt() << row;
        }
    }
    if (oDb->cursorIsEnd(f_oCursor2))
    {
        oDb->cursorClose(f_oCursor2);
        f_oCursor2 = NULL;
    }

    cxPrompt() << CxTime::milliSecondDifferToNow(dtNow);
    cxPrompt() << " --- --- --- --- ---";
}

void timerCursor2(int iInterval)
{
    static int iIndex = 0;
    ++ iIndex;
    msepoch_t dtNow = CxTime::currentSystemTime();
    CxDatabase * oDb = CxDatabaseManager::getDefaultDb();
    if (oDb == NULL)
    {
        cxPrompt() << "can not open database!";
        return;
    }

    cxPrompt() << "DB has cursor count : " << oDb->cursorGetOnlineAll().size();

    string sSql = "select * from omc_performancedata";
    CxDatabase::CursorBase * oCursor = oDb->cursorLoad(sSql, 100);

    cxPrompt() << "oDb->cursorLoad(sSql, 100); " << CxTime::milliSecondDifferToNow(dtNow);

    int iCount = 0;
    while (! oDb->cursorIsEnd(oCursor))
    {
        vector<string> row = oDb->cursorNext(oCursor);
        ++iCount;
    }
    oDb->cursorClose(oCursor);

    cxPrompt() << "oDb->cursorNext(sSql).count :  " << iCount;
    cxPrompt() << "oDb->cursorNext(sSql).all : " << CxTime::milliSecondDifferToNow(dtNow);

    cxPrompt() << " --- --- --- --- ---";
}


void testCursor1()
{
    cxPrompt() << "TEST Cursor1 start : " << CxTime::currentSystemTimeString();
    CxTimerManager::startTimer(timerCursor1, 200);

    CxTimerManager::startTimer(timerCursor2, 1000);
}


void timerCursor3(int iInterval)
{
    static int iIndex = 0;
    ++ iIndex;
    msepoch_t dtNow = CxTime::currentSystemTime();
    CxDatabase * oDb = CxDatabaseManager::getDefaultDb();
    if (oDb == NULL)
    {
        cxPrompt() << "can not open database!";
        return;
    }

    cxPrompt() << "DB has cursor count : " << oDb->cursorGetOnlineAll().size();

    string sSql = "select * from t1";
    CxDatabase::CursorBase * oCursor1 = oDb->cursorLoad(sSql, 10);

    if (oCursor1)
    {
        cxPrompt() << "getColumnNames: ";
        cxPrompt() << oCursor1->getColumnNames();
        cxPrompt() << "getColumnTypes: ";
        cxPrompt() << oCursor1->getColumnTypes();
        cxPrompt() << "getColumnSizes: ";
        cxPrompt() << oCursor1->getColumnSizes();
    }
    if (! oDb->cursorIsEnd(oCursor1)){}
    {
        vector<std::vector<std::string> > rows;
        oDb->cursorPut(oCursor1, rows);
        for (int i = 0; i < rows.size(); ++i)
        {
            vector<string> row = CxEncoding::utf8ToGb2312(rows[i]);
            cxPrompt() << "cursor1 cursorPut row count : " << rows.size()
                       << " , print line" << i << " :";
            cxPrompt() << row;
        }
    }

    cxPrompt() << CxTime::milliSecondDifferToNow(dtNow);
    cxPrompt() << " --- --- --- --- ---";
}

void testCursor2()
{
    cxPrompt() << "TEST Cursor2 start : " << CxTime::currentSystemTimeString();
    CxTimerManager::startTimer(timerCursor3, 1000);
}


