import json
import socket
import pickle

from django.shortcuts import render
from django.http import JsonResponse

ARDUINO_IP = "192.168.0.10"
ARDUINO_PORT = 5600

#modified IP
MESSAGE_RECEIVER_IP = "192.168.0.100"
MESSAGE_RECEIVER_PORT = 8787

COLON_SPLITTER = ":"
SEMICOLON_SPLITTER = ";"
DOT_SPLITTER = "."
SLASH_SPLITTER = "/"
UNDERSCORS_SPLITTER = "_"

ATTR_JSON_MESSAGE_TYPE = "MESSAGE_TYPE"
ATTR_JSON_MOBILE_STATUS_VALUE = "MOBILE_STATUS"
ATTR_JSON_ID_DEVICE = "ID_DEVICE"
ATTR_JSON_NAME_DEVICE = "NAME_DEVICE"
ATTR_JSON_RELAY_STATUS_VALUE = "RELAY_STATUS_VALUE"
ATTR_JSON_RELAY_STATUS_VALUE_ACTIVE = 1
ATTR_JSON_RELAY_STATUS_VALUE_UNACTIVE = 0
ATTR_JSON_ID_ROOM = "ID_ROOM"
ATTR_JSON_DATA = "data"

ATTR_JSON_ID_SD001_VALUE = "SD001"
ATTR_JSON_ID_SD002_VALUE = "SD002"

ATTR_JSON_NAME_DEVICE_LIGHT_VALUE = "DEVICE_LIGHT"
ATTR_JSON_NAME_DEVICE_PLUS_VALUE = "DEVICE_PLUS"

ATTR_JSON_ID_ROOM_R001_VALUE = "R0001"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Create your views here.
def arduino(request):
    return render(request, "arduino.html", {})

def controlSmartPlug(request):
    cmd = request.GET['cmd']

    json_dict_message = {}
    json_message_data = None
    json_dict_message[ATTR_JSON_MESSAGE_TYPE] = str(ATTR_JSON_MOBILE_STATUS_VALUE)

    json_message_data = { \
        ATTR_JSON_ID_DEVICE : str(ATTR_JSON_ID_SD001_VALUE),\
        ATTR_JSON_NAME_DEVICE : str(ATTR_JSON_NAME_DEVICE_LIGHT_VALUE),\
        ATTR_JSON_RELAY_STATUS_VALUE : str(ATTR_JSON_RELAY_STATUS_VALUE_ACTIVE),\
        ATTR_JSON_ID_ROOM : str(ATTR_JSON_ID_ROOM_R001_VALUE)
    }
     
    if cmd == 'OFF':
        json_message_data[ATTR_JSON_RELAY_STATUS_VALUE] = \
                                    str(ATTR_JSON_RELAY_STATUS_VALUE_UNACTIVE)
    json_dict_message[ATTR_JSON_DATA] = json_message_data
    sock.sendto(json.dumps(json_dict_message).encode('utf-8'), (MESSAGE_RECEIVER_IP,\
                                                        MESSAGE_RECEIVER_PORT))
    
    return JsonResponse({'SPState ':cmd})

def function():
    pass