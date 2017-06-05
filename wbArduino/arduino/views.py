import json
import socket
import pickle
import MySQLdb
import string

from arduino import contants

from django.shortcuts import render
from django.http import JsonResponse

# #modified IP
# MESSAGE_RECEIVER_IP = "192.168.0.100"
# MESSAGE_RECEIVER_PORT = 8787

# ATTR_JSON_MESSAGE_TYPE = "MESSAGE_TYPE"
# ATTR_JSON_MOBILE_STATUS_VALUE = "MOBILE_STATUS"
# ATTR_JSON_ID_DEVICE = "ID_DEVICE"
# ATTR_JSON_NAME_DEVICE = "NAME_DEVICE"
# ATTR_JSON_RELAY_STATUS_VALUE = "RELAY_STATUS_VALUE"
# ATTR_JSON_ELECTRIC_STATUS_VALUE = "ELECTRIC_STATUS_VALUE"
# ATTR_JSON_RELAY_STATUS_VALUE_ACTIVE = 1
# ATTR_JSON_RELAY_STATUS_VALUE_UNACTIVE = 0
# ATTR_JSON_ID_ROOM = "ID_ROOM"
# ATTR_JSON_DATA = "data"

# ATTR_JSON_ID_SD001_VALUE = "SD001"
# ATTR_JSON_ID_SD002_VALUE = "SD002"

# ATTR_JSON_NAME_DEVICE_LIGHT_VALUE = "DEVICE_LIGHT"
# ATTR_JSON_NAME_DEVICE_PLUS_VALUE = "DEVICE_PLUS"

# ATTR_JSON_ID_ROOM_R001_VALUE = "R0001"
# #end


# HOST = 'localhost'
# USER = 'root'
# PASSWORD = 'root'
# DATABASE = 'SMARTDEVICE'

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Create your views here.
def arduino(request):
    return render(request, "arduino.html", {})

def selectDevice(cmd):
    # cmd = request.GET['cmd']
    if cmd == 'SEL':
        conn = MySQLdb.connect(host = contants.HOST, user = contants.USER, passwd = contants.PASSWORD, db = contants.DATABASE)
        cur = conn.cursor()
        cur.execute("SELECT nameSmartDevice, stateElectric, stateRelay FROM SmartDevice;")
        json_array = []
        json_dict = {}
        for r in cur:
            if not r is None:
                json_dict={
                    contants.ATTR_JSON_NAME_DEVICE : r[0],\
                    contants.ATTR_JSON_ELECTRIC_STATUS_VALUE : r[1],\
                    contants.ATTR_JSON_RELAY_STATUS_VALUE : r[2]
                }
                json_array.append(json_dict)
        json_dict = {'hang' : json_array}       
        cur.close()
        conn.close()
        return json_dict

def controlSmartPlug(cmd):
    # # cmd = request.GET['cmd']
    # print("CMD2: ", cmd)
    # if cmd == 'ON':
    #     json_dict_on = { 
    #         ATTR_JSON_MESSAGE_TYPE : ATTR_JSON_MOBILE_STATUS_VALUE, \
    #         ATTR_JSON_DATA : { \
    #             ATTR_JSON_ID_DEVICE : "SD001",\
    #             ATTR_JSON_NAME_DEVICE : "DEVICE_LIGHT",\
    #             ATTR_JSON_RELAY_STATUS_VALUE : ATTR_JSON_RELAY_STATUS_VALUE_ACTIVE,\
    #             ATTR_JSON_ID_ROOM : "R001"
    #         }
    #     }
    #     print("CMD ON: ", json_dict_on) 
    #     sock.sendto(json.dumps(json_dict_on).encode(), (MESSAGE_RECEIVER_IP, MESSAGE_RECEIVER_PORT))
        
    # elif cmd == 'OFF':
    #     json_dict_off = { 
    #         ATTR_JSON_MESSAGE_TYPE : ATTR_JSON_MOBILE_STATUS_VALUE, \
    #         ATTR_JSON_DATA : { \
    #             ATTR_JSON_ID_DEVICE : "SD001",\
    #             ATTR_JSON_NAME_DEVICE : "DEVICE_LIGHT",\
    #             ATTR_JSON_RELAY_STATUS_VALUE : ATTR_JSON_RELAY_STATUS_VALUE_UNACTIVE,\
    #             ATTR_JSON_ID_ROOM : "R001"
    #         }
    #     } 
    #     print("CMD OFF: ", json_dict_off)
    #     sock.sendto(json.dumps(json_dict_off).encode(), (MESSAGE_RECEIVER_IP, MESSAGE_RECEIVER_PORT))
    # return JsonResponse({'SPState ':cmd})

    # cmd = request.GET['cmd']
    json_dict_message = {}
    json_message_data = None
    json_dict_message[contants.ATTR_JSON_MESSAGE_TYPE] = str(contants.ATTR_JSON_MOBILE_STATUS_VALUE)

    json_message_data = { \
        contants.ATTR_JSON_ID_DEVICE : str(contants.ATTR_JSON_ID_SD001_VALUE),\
        contants.ATTR_JSON_NAME_DEVICE : str(contants.ATTR_JSON_NAME_DEVICE_LIGHT_VALUE),\
        contants.ATTR_JSON_RELAY_STATUS_VALUE : str(contants.ATTR_JSON_RELAY_STATUS_VALUE_ACTIVE),\
        contants.ATTR_JSON_ID_ROOM : str(contants.ATTR_JSON_ID_ROOM_R001_VALUE)
    }
     
    if cmd == 'OFF':
        json_message_data[contants.ATTR_JSON_RELAY_STATUS_VALUE] = \
                                    str(contants.ATTR_JSON_RELAY_STATUS_VALUE_UNACTIVE)
    json_dict_message[contants.ATTR_JSON_DATA] = json_message_data
    sock.sendto(json.dumps(json_dict_message).encode('utf-8'), (contants.MESSAGE_RECEIVER_IP,\
                                                        contants.MESSAGE_RECEIVER_PORT))
    
    # return JsonResponse({'SPState ':cmd})


def serverDjango(request):
    cmd = request.GET['cmd']
    print("CMD0: ", cmd)
    if cmd == 'ON' or cmd == 'OFF':
        print("CMD1: ", cmd)
        controlSmartPlug(cmd)
        return JsonResponse({'SPState ':cmd})
    elif cmd == 'SEL':
        json_dict = selectDevice(cmd)
        return JsonResponse({'Test: ' : json_dict})


# def selectDevice(request):
#     cmd = request.GET['cmd']
#     if cmd == 'SELECT':
#         conn = MySQLdb.connect(host = HOST, user = USER, passwd = PASSWORD, db = DATABASE)
#         cur = conn.cursor()
#         cur.execute("SELECT nameSmartDevice, stateElectric, stateRelay FROM SmartDevice;")
#         json_dict = {}
#         for r in cur:
#             if not r is None:
#                 json_dict={
#                     ATTR_JSON_NAME_DEVICE : r[0],\
#                     ATTR_JSON_ELECTRIC_STATUS_VALUE : r[1],\
#                     ATTR_JSON_RELAY_STATUS_VALUE : r[2]
#                 }
#                 print("JSON ", json_dict)
#                 return JsonResponse({'Test: ' : json_dict})
#         cur.close()
#         conn.close()

# def controlSmartPlug(request):
#     cmd = request.GET['cmd']
#     if cmd == 'ON':
#         json_dict_on = { 
#             ATTR_JSON_MESSAGE_TYPE : ATTR_JSON_MOBILE_STATUS_VALUE, \
#             ATTR_JSON_DATA : { \
#                 ATTR_JSON_ID_DEVICE : "SD001",\
#                 ATTR_JSON_NAME_DEVICE : "DEVICE_LIGHT",\
#                 ATTR_JSON_RELAY_STATUS_VALUE : ATTR_JSON_RELAY_STATUS_VALUE_ACTIVE,\
#                 ATTR_JSON_ID_ROOM : "R001"
#             }
#         }
#         print("CMD ON: ", json_dict_on) 
#         sock.sendto(json.dumps(json_dict_on).encode(), (MESSAGE_RECEIVER_IP, MESSAGE_RECEIVER_PORT))
        
#     elif cmd == 'OFF':
#         json_dict_off = { 
#             ATTR_JSON_MESSAGE_TYPE : ATTR_JSON_MOBILE_STATUS_VALUE, \
#             ATTR_JSON_DATA : { \
#                 ATTR_JSON_ID_DEVICE : "SD001",\
#                 ATTR_JSON_NAME_DEVICE : "DEVICE_LIGHT",\
#                 ATTR_JSON_RELAY_STATUS_VALUE : ATTR_JSON_RELAY_STATUS_VALUE_UNACTIVE,\
#                 ATTR_JSON_ID_ROOM : "R001"
#             }
#         } 
#         print("CMD OFF: ", json_dict_off)
#         sock.sendto(json.dumps(json_dict_off).encode(), (MESSAGE_RECEIVER_IP, MESSAGE_RECEIVER_PORT))
    
#     return JsonResponse({'SPState ':cmd})

