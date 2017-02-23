#ifndef __DBSMARTPLUG_FOR_C_H__
#define __DBSMARTPLUG_FOR_C_H__

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
//bool update_to_db_ForC(const SmartDeviceInfo* smartplug);
bool update_to_db_ForC(const char* stateElectric, const char* stateRelay, const char* ip_port_jack);

#ifdef __cplusplus
}
#endif

#endif