/*****************************************************************************/
/*!
 * @file JsonParser.cpp
 * @brief
 *
 * Copyright (c) Tien Nguyen Anh
 *
 * @detail 
 *
 * Modified History
 * ---------------
 * 2017-Jan-05 Created tien.nguyenanh94@gmail.com
 * 2017-Jan-07 Modified tn-trang.tran@outlook.com
 * 2017-Jan-11 Modified tn-trang.tran@outlook.com
 * 2017-Jan-18 Modified tn-trang.tran@outlook.com
 */
/*****************************************************************************/

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "JsonParser.h"

#ifdef UNITTEST
#define STATIC
#else
#define STATIC static
#endif

/*!
 * @internal
 */
STATIC std::string getJsonPath(const std::string& source,
                                            const std::string& destination)
{
    std::string jsonPath;
    jsonPath.append(source);
    jsonPath.append(JSON_PATH_SPLITTER);
    jsonPath.append(destination);

    return jsonPath;
}

/*!
 * @internal
 */
bool parseSmartPlugStatusJson(const std::string& jsonString,
                                                SmartPlugInfo& info)
{
    boost::property_tree::ptree pTree;
    
    if (jsonString.compare("") == 0)
    {
        return false;
    }

    if (!convertJsonStrToPtree(jsonString, pTree))
    {
        return false;
    }

    /*!
     * Parse Information of Sender
     */
    std::string jsonIPPath = getJsonPath(ATTR_JSON_SENDER, ATTR_JSON_IP);
    std::string ipStr = pTree.get<std::string>(jsonIPPath);

    std::string jsonPortPath = getJsonPath(ATTR_JSON_SENDER, ATTR_JSON_PORT);
    std::string portStr = pTree.get<std::string>(jsonPortPath);

    std::string jsonSmartPlugStatusPath = getJsonPath(ATTR_JSON_DATA,
                                                ATTR_JSON_SMART_PLUG_STATUS_VALUE);
    std::string smartPlugStatusStr = 
                        pTree.get<std::string>(jsonSmartPlugStatusPath);

    std::string jsonDateTimeMonth = getJsonPath(ATTR_JSON_MOMENT, ATTR_JSON_MONTH);
    std::string monthStr = pTree.get<std::string>(jsonDateTimeMonth);

    std::string jsonDateTimeDay = getJsonPath(ATTR_JSON_MOMENT, ATTR_JSON_DAY);
    std::string dayStr = pTree.get<std::string>(jsonDateTimeDay);

    std::string jsonDateTimeYear = getJsonPath(ATTR_JSON_MOMENT, ATTR_JSON_YEAR);
    std::string yearStr = pTree.get<std::string>(jsonDateTimeYear);

    std::string jsonDateTimeHour = getJsonPath(ATTR_JSON_MOMENT, ATTR_JSON_HOUR);
    std::string hourStr = pTree.get<std::string>(jsonDateTimeHour);

    std::string jsonDateTimeMinutes = getJsonPath(ATTR_JSON_MOMENT, ATTR_JSON_MINUTES);
    std::string minutesStr = pTree.get<std::string>(jsonDateTimeMinutes);

    std::string jsonDateTimeSecond = getJsonPath(ATTR_JSON_MOMENT, ATTR_JSON_SECOND);
    std::string secondStr = pTree.get<std::string>(jsonDateTimeSecond);


    strcpy(info.data.smartPlugStatus, smartPlugStatusStr.c_str());

    info.datetimesp.month = std::stol(monthStr);
    info.datetimesp.day = std::stol(dayStr);
    info.datetimesp.year = std::stol(yearStr);
    info.datetimesp.hour = std::stol(hourStr);
    info.datetimesp.min = std::stol(minutesStr);
    info.datetimesp.sec = std::stol(secondStr);

    info.sender.port = std::stol(portStr);
    strcpy(info.sender.ip, ipStr.c_str());
}