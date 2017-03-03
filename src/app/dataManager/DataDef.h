#ifndef __DATA_STRUCT_DEF_H__
#define __DATA_STRUCT_DEF_H__

#define MAX_SMART_DEVICE_STATUS_VALUE 102

#define JSON_TOKEN_SIZE 3
#define JSON_DATA_SIZE 4
#define SENDER_TOKEN_SIZE 2
#define DATE_TIME_TOKEN_SIZE 3
#define STATUS_TOKEN_SIZE 2

#define COLON_SPLITTER ":"
#define SEMICOLON_SPLITTER ";"
#define DOT_SPLITTER "."
#define SLASH_SPLITTER "/"
#define UNDERSCORS_SPLITTER "_"

#define ATTR_JSON_MESSAGE_TYPE "MESSAGE_TYPE"
#define ATTR_JSON_MESSAGE_TYPE_VALUE "SMART_DEVICE_STATUS_VALUE"

#define ATTR_JSON_ID_DEVICE "ID_DEVICE"

#define ATTR_JSON_RELAY_STATUS_VALUE "RELAY_STATUS_VALUE"
#define ATTR_JSON_RELAY_STATUS_VALUE_ACTIVE "ACTIVE"
#define ATTR_JSON_RELAY_STATUS_VALUE_UNACTIVE "UNACTIVE"

#define ATTR_JSON_ELECTRIC_STATUS_VALUE "ELECTRIC_STATUS_VALUE"
#define ATTR_JSON_ELECTRIC_MESSAGE_VALUE_ON "ON"
#define ATTR_JSON_ELECTRIC_MESSAGE_VALUE_OFF "OFF"

#define ATTR_JSON_IP_PORT_VALUE "IP_PORT"
#define ATTR_JSON_ID_ROOM_VALUE "ID_ROOM"
#define ATTR_JSON_ID_TIMER_VALUE "ID_TIMER"

#define MESSAGE_TYPE_DEFAULT_VALUE "MESSAGE_TYPE_DEFAULT"
#define MESSAGE_TYPE_SMART_DEVICE_STATUS_VALUE "SMART_DEVICE_STATUS_VALUE"

#define ATTR_JSON_DATA "data"

#define ATTR_JSON_TIMER "timer"
#define ATTR_JSON_YEAR "Year"
#define ATTR_JSON_MONTH "Month"
#define ATTR_JSON_DAY "Day"
#define ATTR_JSON_HOUR "Hour"
#define ATTR_JSON_MINUTES "Minutes"
#define ATTR_JSON_SECOND "Second"

#define ATTR_JSON_SENDER "sender"
#define ATTR_JSON_IP "IP"
#define ATTR_JSON_PORT "Port"

typedef enum
{
    MESSAGE_TYPE_DEFAULT = -1,
    MESSAGE_TYPE_SMART_DEVICE_STATUS,
}MESSAGE_TYPE;

typedef struct
{
    char ip[20];
    long port;
}Sender;

typedef struct
{
    char idTimer[10];
    int secSD;
    int minSD;
    int hourSD;
    int daySD;
    int monthSD;
    int yearSD;
}Timer;

typedef struct 
{
    char idSmartDevice[10];
    char idRoom[10];
    char nameSmartDevice [20];
    char ip_port[20];
}SmartDevice;

typedef struct
{
    char idTimer[10];
    char idSmartDevice[10];
    char stateElectric[10];
    char stateRelay[10];
}Device_Timer;

typedef struct
{
    char idRoom[10];
    char nameRoom[20];
}Room;

typedef struct 
{    
    char idUser[10];
    char nameUser[20];
    char password[20];
    char stateUser[10];
    char idUserStyle[10];
}User;

typedef struct
{
    char idUserStyle[10];
    char nameUserStyle[20];
}UserStyle;

typedef struct
{
    char idUserGuide[10];
    char nameUserGuide[20];
}UserGuide;

typedef struct
{
    SmartDevice device;
    Device_Timer device_timer;
    Sender sender;
    Timer timer;
}SmartDeviceInfo;

#endif