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
 * 2017-Feb-11 Modified tn-trang.tran@outlook.com
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
    jsonPath.append(DOT_SPLITTER);
    jsonPath.append(destination);

    return jsonPath;
}

/*!
 * @internal
 */
bool parseDataSmartDeviceJson(const std::string& jsonString,
                                                SmartDeviceInfo& info)
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
     * Parse Information of IdSmartPlug
     */
    std::string jsonIdSmartDevicePath = getJsonPath(ATTR_JSON_DATA,
                                                ATTR_JSON_ID_DEVICE);
    std::string idSmartDeviceStr = pTree.get<std::string>(jsonIdSmartDevicePath);

    /*!
     * Parse Information of Relay Status Value
     */
    std::string jsonRalayStatusValuePath = getJsonPath(ATTR_JSON_DATA,
                                                ATTR_JSON_RELAY_STATUS_VALUE);
    std::string relayStatusValueStr = pTree.get<std::string>(jsonRalayStatusValuePath);

    /*!
     * Parse Information of Electric Status Value
     */
    std::string jsonElectricStatusValuePath = getJsonPath(ATTR_JSON_DATA,
                                                ATTR_JSON_ELECTRIC_STATUS_VALUE);
    std::string electricStatusValueStr = pTree.get<std::string>(jsonElectricStatusValuePath);

    /*!
     * Parse Information of ID_ROOM
     */
    std::string idRoomPath = getJsonPath(ATTR_JSON_DATA, 
                                                ATTR_JSON_ID_ROOM_VALUE);
    std::string idRoomStr = pTree.get<std::string>(idRoomPath);

    /**!
     ** Parse Information of IP Address
     **/
    std::string jsonIPPath = getJsonPath(ATTR_JSON_SENDER, ATTR_JSON_IP);
    std::string ipStr = pTree.get<std::string>(jsonIPPath);

    /**!
     ** Parse Information of Port
     **/
    std::string jsonPortPath = getJsonPath(ATTR_JSON_SENDER, ATTR_JSON_PORT);
    std::string portStr = pTree.get<std::string>(jsonPortPath);
    
    /**!
     ** Parse Information of ID_TIMER
     **/
    std::string jsonIdTimerPath = getJsonPath(ATTR_JSON_TIMER,
                                                ATTR_JSON_ID_TIMER_VALUE);
    std::string idTimerStr = pTree.get<std::string>(jsonIdTimerPath);

    /**!
     ** Parse Information of Timer of Month
     **/
    std::string jsonDateTimeMonth = getJsonPath(ATTR_JSON_TIMER, ATTR_JSON_MONTH);
    std::string monthStr = pTree.get<std::string>(jsonDateTimeMonth);

    /**!
     ** Parse Information of Timer of Day
     **/
    std::string jsonDateTimeDay = getJsonPath(ATTR_JSON_TIMER, ATTR_JSON_DAY);
    std::string dayStr = pTree.get<std::string>(jsonDateTimeDay);

    /**!
     ** Parse Information of Timer of Year
     **/
    std::string jsonDateTimeYear = getJsonPath(ATTR_JSON_TIMER, ATTR_JSON_YEAR);
    std::string yearStr = pTree.get<std::string>(jsonDateTimeYear);

    /**!
     ** Parse Information of Timer of Hour
     **/
    std::string jsonDateTimeHour = getJsonPath(ATTR_JSON_TIMER, ATTR_JSON_HOUR);
    std::string hourStr = pTree.get<std::string>(jsonDateTimeHour);

    /**!
     ** Parse Information of Timer of Minutes
     **/
    std::string jsonDateTimeMinutes = getJsonPath(ATTR_JSON_TIMER, ATTR_JSON_MINUTES);
    std::string minutesStr = pTree.get<std::string>(jsonDateTimeMinutes);

    std::string jsonDateTimeSecond = getJsonPath(ATTR_JSON_TIMER, ATTR_JSON_SECOND);
    std::string secondStr = pTree.get<std::string>(jsonDateTimeSecond);

    /**!
     ** Put value into Structure
     **/
    strcpy(info.deviceTimer.idSmartDevice, idSmartDeviceStr.c_str());
    strcpy(info.deviceTimer.stateRelay, relayStatusValueStr.c_str());
    strcpy(info.deviceTimer.stateElectric, electricStatusValueStr.c_str());
    strcpy(info.device.idRoom, idRoomStr.c_str());

    strcpy(info.timer.idTimer, idTimerStr.c_str());
    info.timer.monthSD = std::stol(monthStr);
    info.timer.daySD = std::stol(dayStr);
    info.timer.yearSD = std::stol(yearStr);
    info.timer.hourSD = std::stol(hourStr);
    info.timer.minSD = std::stol(minutesStr);
    info.timer.secSD = std::stol(secondStr);

    info.sender.port = std::stol(portStr);
    strcpy(info.sender.ip, ipStr.c_str());
}