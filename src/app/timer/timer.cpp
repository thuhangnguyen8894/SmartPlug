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
 * 2017-Jan-23 Modified tn-trang.tran@outlook.com
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

    /*
     * handle time
     */
    unsigned int yearInt = YEAR + ltm->tm_year;
    unsigned int monthInt = MONTH + ltm->tm_mon;
    unsigned int dayInt = ltm->tm_mday;
    unsigned int hourInt = ltm->tm_hour;
    unsigned int minInt = ltm->tm_min;
    unsigned int secInt = ltm->tm_sec;

    std::stringstream yearStream;;
    yearStream << yearInt;
    std::string yearStr= yearStream.str();

    std::stringstream monthStream;;
    monthStream << monthInt;
    std::string monthStr= monthStream.str();

    std::stringstream dayStream;;
    dayStream << dayInt;
    std::string dayStr= dayStream.str();

    std::stringstream hourStream;;
    hourStream << hourInt;
    std::string hourStr= hourStream.str();

    std::stringstream minStream;;
    minStream << minInt;
    std::string minStr= minStream.str();

    std::stringstream secStream;;
    secStream << secInt;
    std::string secStr= secStream.str();

    std::string dateTimeStr = monthStr + SLASH_SPLITTER + dayStr + SLASH_SPLITTER + yearStr 
                              + UNDERSCORS_SPLITTER + hourStr + COLON_SPLITTER + minStr + COLON_SPLITTER + secStr;

    int lenDateTime = dateTimeStr.length();
    char* dateTimeChar = new char[lenDateTime + 1];
    strcpy(dateTimeChar, dateTimeStr.c_str());

    return dateTimeChar;
}