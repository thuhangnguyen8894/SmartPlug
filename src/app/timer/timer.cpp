/*
 * @file timer.cpp
 * @brief Handle timer of system insert into processor.
 *
 * Copyright (c) 2017 Trang Tran
 *
 * @detail
 *
 * Modified History
 * ---------------
 * 2017-Jan-22 Created tn-trang.tran@outlook.com
 */

#include "timer.h"


char* timer()
{
	/*
     * define time_t, use handle current time
     */
    time_t now = time(0);
    tm *ltm = localtime(&now);
    /*
     * the end
     */

    char* datetime = new char[20];

    /*
     * handle time
     */
    unsigned int year = YEAR + ltm->tm_year;
    unsigned int month = MONTH + ltm->tm_mon;
    unsigned int day = ltm->tm_mday;
    unsigned int hour = ltm->tm_hour;
    unsigned int min = ltm->tm_min;
    unsigned int sec = ltm->tm_sec;

    std::string strYear = std::to_string(year);
    std::string strMonth = std::to_string(month);
    std::string strDay = std::to_string(day);
    std::string strHour = std::to_string(hour);
    std::string strMin = std::to_string(min);
    std::string strSec = std::to_string(sec);

    /*
     * the end handle time
     */

    /*
     * Appending IP of Sender to message
     * Appending datetime of DatetimeSP to message
     */
    strcat(datetime, SENSOR_MESSAGE_SPLITTER);
    strcat(datetime, strMonth.c_str());
    strcat(datetime, DATE_TIME_SLASH);
    strcat(datetime, strDay.c_str());
    strcat(datetime, DATE_TIME_SLASH);
    strcat(datetime, strYear.c_str());
    strcat(datetime, DATE_TIME_SPACE);
    strcat(datetime, strHour.c_str());
    strcat(datetime, IP_PORT_REGEX_SPLITTER);
    strcat(datetime, strMin.c_str());
    strcat(datetime, IP_PORT_REGEX_SPLITTER);
    strcat(datetime, strSec.c_str());

    return datetime;
}