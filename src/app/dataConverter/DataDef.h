#ifndef __DATA_STRUCT_DEF_H__
#define __DATA_STRUCT_DEF_H__

#define MAX_SENSOR_MESSAGE_LENGTH 5
#define IP_PORT_TOKEN_SIZE 2

#define SMART_PLUG_MESSAGE_TYPE 'S'
#define SMART_PLUG_MESSAGE_VALUE_ON 'N'
#define SMART_PLUG_MESSAGE_VALUE_OFF 'F'

#define ATTR_JSON_MESSAGE_TYPE "MESSAGE_TYPE"
#define ATTR_JSON_SMART_PLUG_STATUS "SMART_PLUG_STATUS"

#define LIGHT_INTENSITY_TOPIC "SMART_PLUG_STATUS"
#define CONTROL_SMART_PLUG_TOPIC "LIGHT_CONTROL_SMART_PLUG_TOPIC"

#define ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_OFF "OFF"
#define ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_ON "ON"
#define MESSAGE_TYPE_SMART_PLUG_STATUS_STR "SMART_PLUG_STATUS"
#define MESSAGE_TYPE_CONTROL_SMART_PLUG_STR "CONTROL_SMART_PLUG"

#define ATTR_JSON_DATA "data"
#define ATTR_JSON_MOMENT "moment"

#define ATTR_JSON_IP "IP"
#define ATTR_JSON_PORT "Port"
#define ATTR_JSON_SENDER "Sender"

typedef enum
{
    MESSAGE_TYPE_DEFAULT = -1,
    MESSAGE_TYPE_SMART_PLUG_STATUS,
    MESSAGE_TYPE_CONTROL_SMART_PLUG
}MESSAGE_TYPE;

typedef struct
{
    char ip[20];
    long port;
}Sender;

typedef struct
{
    long smartplug;
}smartplug;

typedef struct
{
    smartplug data;
    Sender sender;
}smartplugInfo;

#endif
