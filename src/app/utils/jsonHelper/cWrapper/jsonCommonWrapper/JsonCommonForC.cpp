/***************************************************************************/
/*!
 * @file JsonCommonForC.c
 * @brief
 *
 * Copyright (c) Tien Nguyen Anh
 *
 * @detail
 *
 * Modified History
 * ---------------
 * 2017-Jan-06 Created tien.nguyenanh94@gmail.com
 */
/***************************************************************************/

#include "JsonCommon.h"
#include "JsonCommonForC.h"

/*!
 * @internal
 */
void getJSONMessageTypeForC(const char* message, MESSAGE_TYPE* messageType)
{
	switch(message[0]) 
    {
    case SMART_PLUG_MESSAGE_TYPE:
        return MESSAGE_TYPE_SMART_PLUG_STATUS;
    case SMART_PLUG_MESSAGE_VALUE_ON:
        return MESSAGE_TYPE_SMART_PLUG_STATUS;
    case SMART_PLUG_MESSAGE_VALUE_OFF:
        return MESSAGE_TYPE_SMART_PLUG_STATUS;
    default:
        return MESSAGE_TYPE_DEFAULT;
    }
}

/*!
 * @internal
 */
char* convertMessageTypeToStrForC(const MESSAGE_TYPE* messageType)
{
	switch(messageType)
    {
    case MESSAGE_TYPE_SMART_PLUG_STATUS:
        return MESSAGE_TYPE_SMART_PLUG_STATUS_STR;
    case MESSAGE_TYPE_CONTROL_SMART_PLUG:
        return MESSAGE_TYPE_CONTROL_SMART_PLUG_STR;
    default:
        return "MESSAGE_TYPE_DEFAULT";
    }
}

/*!
 * @internal
 */
bool isSensorMessageForC(const char* message)
{
    if (strlen(message) > MAX_SENSOR_MESSAGE_LENGTH
        || strlen(message) <= 0)
    {
        return false;
    }

    return true;
}