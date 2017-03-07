#ifndef __DBSMARTDEVICE_FOR_C_H__
#define __DBSMARTDEVICE_FOR_C_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "DataDef.h"

#ifdef __cplusplus
extern "C"{
#endif

/*!
 * @brief
 * param[in] message
 * return
 */
bool insert_to_table_Timer_ForC(const SmartDeviceInfo* device);

bool insert_to_table_Device_Timer_ForC(const SmartDeviceInfo* device);

bool select_idTimer_to_table_Timer_ForC(SmartDeviceInfo* device);

#ifdef __cplusplus
}
#endif

#endif