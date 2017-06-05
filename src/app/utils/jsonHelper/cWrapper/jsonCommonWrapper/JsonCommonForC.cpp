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
 * 2017-Jan-12 Modified tn-trang.tran@outlook.com
 * 2017-Jan-18 Modified tn-trang.tran@outlook.com
 */
/***************************************************************************/

#include "JsonCommon.h"
#include "JsonCommonForC.h"

/*!
 * @internal
 */
void getJSONMessageTypeForC(const char* message, MESSAGE_TYPE* messageType)
{
    *messageType = getJSONMessageType(std::string(message));
}

/*!
 * @internal
 */
bool isSensorMessageForC(const char* message)
{

    return isSensorMessage(std::string(message));
}