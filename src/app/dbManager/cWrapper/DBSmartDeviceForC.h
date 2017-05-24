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
bool insertToTableTimerForC(const SmartDeviceInfo* device);

bool insertToTableDeviceTimerForC(const SmartDeviceInfo* device);

bool selectIdTimerToTableTimerForC(SmartDeviceInfo* device);

bool selectDeviceToTableSmartDeviceForC(SmartDeviceInfo** device, 
                                                        int *numberOfElement);

#ifdef __cplusplus
}
#endif

#endif