#ifndef __DATA_STRUCT_DEF_H__
#define __DATA_STRUCT_DEF_H__

#define MAX_SENSOR_MESSAGE_LENGTH 70
#define JSON_TOKEN_SIZE 4
#define JSON_DATA_SIZE 3
#define IP_PORT_TOKEN_SIZE 2
#define DATE_TIME_TOKEN_SIZE 2
#define STATUS_TOKEN_SIZE 2

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
#define ATTR_JSON_ELECTRIC_STATUS_VALUE "ELECTRIC_STATUS_VALUE"
#define ATTR_JSON_JACK_RELAY_VALUE "JACK_RELAY_VALUE"
#define ATTR_JSON_IP_PORT_JACK_VALUE "IP_PORT_JACK"

#define ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_OFF "OFF"
#define ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_ON "ON"

#define ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_P_OFF "POFF"
#define ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_P_ON "PON"

#define ATTR_JSON_ELECTRIC_MESSAGE_VALUE_ACTIVE "ACTIVE"
#define ATTR_JSON_ELECTRIC_MESSAGE_VALUE_UNACTIVE "UNACTIVE"

#define ATTR_JSON_JACK_RELAY_VALUE_9 "9"
#define ATTR_JSON_JACK_RELAY_VALUE_8 "8"
#define ATTR_JSON_JACK_RELAY_VALUE_7 "7"
#define ATTR_JSON_JACK_RELAY_VALUE_6 "6"
#define ATTR_JSON_JACK_RELAY_VALUE_5 "5"
#define ATTR_JSON_JACK_RELAY_VALUE_4 "4"

#define MESSAGE_TYPE_SMART_PLUG_STATUS_STR "SMART_PLUG_STATUS_VALUE"

#define ATTR_JSON_DATA "data"

#define ATTR_JSON_MOMENT "moment"
#define ATTR_JSON_YEAR "Year"
#define ATTR_JSON_MONTH "Month"
#define ATTR_JSON_DAY "Day"
#define ATTR_JSON_HOUR "Hour"
#define ATTR_JSON_MINUTES "Minutes"
#define ATTR_JSON_SECOND "Second"

#define ATTR_JSON_ID "id"
#define ATTR_JSON_ID_TABLE_TIMER "ID_TABLE_Timer"

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
    char status_use_electric[5];
    char status_electric[10];
    char jack_relay[2];
    char ip_port_jack[20];
}SmartDevice;

typedef struct 
{
    char id_timer[10];
}IDAnything;

typedef struct
{
    SmartDevice data;
    Sender sender;
    IDAnything id;
    DatetimeSP datetimesp;
}SmartDeviceInfo;

#endif