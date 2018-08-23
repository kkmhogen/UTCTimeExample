// UTCTimeTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "UTCTools.h"
#include <iostream>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	UTCTimeStruct utcStru;
	char buffer[40];

	utcStru.year = 2018;
	utcStru.month = 8;
	utcStru.day = 10;
	utcStru.hour = 16;
	utcStru.minutes = 10;
	utcStru.seconds = 0;
	sprintf(buffer, "Old UTC Time:%d-%d-%d %d:%d:%d", utcStru.year,
		utcStru.month, utcStru.day, utcStru.hour, utcStru.minutes, utcStru.seconds);
	cout<<buffer<<endl;

	UTCTime utcTime = UTC_convertUTCSecs(&utcStru);
	cout<<"Old UTC seconds:"<<utcTime<<endl;

	utcTime += 500;

	UTCTimeStruct utcNewStru;
	UTC_convertUTCTime(utcTime, &utcNewStru);
	cout<<"After increase utc time by 500 seconds."<<endl;
	sprintf(buffer, "New UTC Time:%d-%d-%d %d:%d:%d", utcNewStru.year,
		utcNewStru.month, utcNewStru.day, utcNewStru.hour, utcNewStru.minutes, utcNewStru.seconds);
	cout<<buffer<<endl;
	cout<<"New UTC seconds:"<<utcTime<<endl;

	return 0;
}

