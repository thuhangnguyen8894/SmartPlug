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
ATTR_JSON_RELAY_STATUS_VALUE_ACTIVE = "ACTIVE"
ATTR_JSON_RELAY_STATUS_VALUE_UNACTIVE = "UNACTIVE"
ATTR_JSON_ID_ROOM = "ID_ROOM"
ATTR_JSON_DATA = "data"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Create your views here.
def arduino(request):
    return render(request, "arduino.html", {})

def controlSmartPlug(request):
    cmd = request.GET['cmd']

    # json_dict = {"a" : 1, "b" : "dummy_data"}
    # if cmd == 'ON' or cmd == 'OFF':
    #     sock.sendto(cmd.encode(), (MESSAGE_RECEIVER_IP, MESSAGE_RECEIVER_PORT))
    # sock.sendto(json.dumps(json_dict).encode(), (MESSAGE_RECEIVER_IP, MESSAGE_RECEIVER_PORT))
    # sock.sendto("SMART_DEVICE_STATUS_VALUE;SD001:DEVICE_LIGHT:OFF:UNACTIVE:R0001".encode(), (MESSAGE_RECEIVER_IP, MESSAGE_RECEIVER_PORT))

    if cmd == 'ON':
        json_dict_on = { 
            ATTR_JSON_MESSAGE_TYPE : ATTR_JSON_MOBILE_STATUS_VALUE, \
            ATTR_JSON_DATA : { \
                ATTR_JSON_ID_DEVICE : "SD001",\
                ATTR_JSON_NAME_DEVICE : "DEVICE_LIGHT",\
                ATTR_JSON_RELAY_STATUS_VALUE : ATTR_JSON_RELAY_STATUS_VALUE_ACTIVE,\
                ATTR_JSON_ID_ROOM : "R001"
            }
        }
        print("CMD ON: ", json_dict_on) 
        sock.sendto(json.dumps(json_dict_on).encode(), (MESSAGE_RECEIVER_IP, MESSAGE_RECEIVER_PORT))
        # sock.sendto("SMART_DEVICE_STATUS_VALUE;SD001:DEVICE_LIGHT:ON:ACTIVE:R0001".encode(), (MESSAGE_RECEIVER_IP, MESSAGE_RECEIVER_PORT))
        
    elif cmd == 'OFF':
        json_dict_off = { 
            ATTR_JSON_MESSAGE_TYPE : ATTR_JSON_MOBILE_STATUS_VALUE, \
            ATTR_JSON_DATA : { \
                ATTR_JSON_ID_DEVICE : "SD001",\
                ATTR_JSON_NAME_DEVICE : "DEVICE_LIGHT",\
                ATTR_JSON_RELAY_STATUS_VALUE : ATTR_JSON_RELAY_STATUS_VALUE_UNACTIVE,\
                ATTR_JSON_ID_ROOM : "R001"
            }
        } 
        print("CMD OFF: ", json_dict_off)
        sock.sendto(json.dumps(json_dict_off).encode(), (MESSAGE_RECEIVER_IP, MESSAGE_RECEIVER_PORT))
        # sock.sendto("SMART_DEVICE_STATUS_VALUE;SD001:DEVICE_LIGHT:OFF:UNACTIVE:R0001".encode(), (MESSAGE_RECEIVER_IP, MESSAGE_RECEIVER_PORT))
    
    return JsonResponse({'SPState ':cmd})
