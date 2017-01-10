/***************************************************************************/
/*!
 * @file JsonCommonForC.h
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

#ifndef __JSONCOMMON_FOR_C_H__
#define __JSONCOMMON_FOR_C_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"{
#endif

/*!
 * @brief
 * param[in] message
 * return
 */
void getJSONMessageTypeForC(const char* message, MESSAGE_TYPE* messageType);

/*!
 * @brief
 * param[in] message
 * return
 */
char* convertMessageTypeToStrForC(const MESSAGE_TYPE* messageType);

/*!
 * @brief
 * param[in] message
 * return
 */
bool isSensorMessageForC(const char* message);

/*!
 * @brief
 * param[in] message
 * return
 */
bool convertArduinoMsgToInt16ForC(const char* msg, uint16_t* value);

#ifdef __cplusplus
}
#endif

#endif