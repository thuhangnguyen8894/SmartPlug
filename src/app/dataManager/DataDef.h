#ifndef __DATA_STRUCT_DEF_H__
#define __DATA_STRUCT_DEF_H__

#define MAX_SENSOR_MESSAGE_LENGTH 70
#define JSON_TOKEN_SIZE 3
#define IP_PORT_TOKEN_SIZE 2
#define DATE_TIME_TOKEN_SIZE 2

#define SIZE_COUNT_DEVICE 2
#define SIZE_NAME_DEVICE 20

#define SIZE_IP 20
#define SIZE_NAME_ROOM 20

#define SIZE_ID 10

#define IP_PORT_REGEX_SPLITTER ":"
#define SENSOR_MESSAGE_SPLITTER ";"
#define JSON_PATH_SPLITTER "."
#define DATE_TIME_SLASH "/"
#define DATE_TIME_SPACE "  "

#define SMART_PLUG_MESSAGE_VALUE 'P'

#define ATTR_JSON_MESSAGE_TYPE "MESSAGE_TYPE"
#define ATTR_JSON_SMART_PLUG_STATUS_VALUE "SMART_PLUG_STATUS_VALUE"

#define ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_OFF "OFF"
#define ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_ON "ON"

#define ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_P_OFF "POFF"
#define ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_P_ON "PON"

#define MESSAGE_TYPE_SMART_PLUG_STATUS_STR "SMART_PLUG_STATUS_VALUE"

#define ATTR_JSON_DATA "data"

#define ATTR_JSON_MOMENT "moment"
#define ATTR_JSON_YEAR "Year"
#define ATTR_JSON_MONTH "Month"
#define ATTR_JSON_DAY "Day"
#define ATTR_JSON_HOUR "Hour"
#define ATTR_JSON_MINUTES "Minutes"
#define ATTR_JSON_SECOND "Second"

#define ATTR_JSON_IP "IP"
#define ATTR_JSON_PORT "Port"
#define ATTR_JSON_SENDER "Sender"

typedef enum
{
    MESSAGE_TYPE_DEFAULT = -1,
    MESSAGE_TYPE_SMART_PLUG_STATUS,
}MESSAGE_TYPE;

typedef struct
{
    char ip[SIZE_IP];
    long port;
}Sender;

typedef struct
{
    int secSP;
    int minSP;
    int hourSP;
    int daySP;
    int monthSP;
    int yearSP;
}DatetimeSP;

typedef struct
{
    Data data;
    Sender sender;
    DatetimeSP datetimesp;
}SmartDeviceInfo;

typedef struct 
{
    char nameDevice[SIZE_NAME_DEVICE];
    char quality[SIZE_COUNT_DEVICE];
    char onDevice[SIZE_COUNT_DEVICE];
    char activeDevice[SIZE_COUNT_DEVICE];
    char offDevice[SIZE_COUNT_DEVICE];
    char inactiveDevice[SIZE_COUNT_DEVICE];
}SmartDevice;

typedef struct 
{
    SmartDevice smartDevice;
    char nameRoom[SIZE_NAME_ROOM];
}Data;

#endif