import json
import socket
import pickle
import MySQLdb
import string

from arduino import constants

from django.shortcuts import render
from django.http import JsonResponse

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Create your views here.
def arduino(request):
    return render(request, "arduino.html", {})

def selectDevice(cmd):
    # cmd = request.GET['cmd']
    if cmd == 'SEL':
        conn = MySQLdb.connect(host = constants.HOST, user = constants.USER, passwd = constants.PASSWORD, db = constants.DATABASE)
        cur = conn.cursor()
        cur.execute("SELECT idSmartDevice, nameSmartDevice, stateElectric, stateRelay FROM SmartDevice;")
        json_array = []
        for r in cur:
            if not r is None:
                json_dict={
                    constants.ATTR_JSON_ID_DEVICE : r[0],\
                    constants.ATTR_JSON_NAME_DEVICE : r[1],\
                    constants.ATTR_JSON_ELECTRIC_STATUS_VALUE : r[2],\
                    constants.ATTR_JSON_RELAY_STATUS_VALUE : r[3]
                }
                json_array.append(json_dict)   
        print(json_array)  
        cur.close()
        conn.close()
        return json_array

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
    json_dict_message[constants.ATTR_JSON_MESSAGE_TYPE] = str(constants.ATTR_JSON_MOBILE_STATUS_VALUE)

    json_message_data = { \
        constants.ATTR_JSON_ID_DEVICE : str(constants.ATTR_JSON_ID_SD001_VALUE),\
        constants.ATTR_JSON_NAME_DEVICE : str(constants.ATTR_JSON_NAME_DEVICE_LIGHT_VALUE),\
        constants.ATTR_JSON_RELAY_STATUS_VALUE : str(constants.ATTR_JSON_RELAY_STATUS_VALUE_ACTIVE),\
        constants.ATTR_JSON_ID_ROOM : str(constants.ATTR_JSON_ID_ROOM_R001_VALUE)
    }
     
    if cmd == 'OFF':
        json_message_data[constants.ATTR_JSON_RELAY_STATUS_VALUE] = \
                                    str(constants.ATTR_JSON_RELAY_STATUS_VALUE_UNACTIVE)
    json_dict_message[constants.ATTR_JSON_DATA] = json_message_data
    sock.sendto(json.dumps(json_dict_message).encode('utf-8'), (constants.MESSAGE_RECEIVER_IP,\
                                                        constants.MESSAGE_RECEIVER_PORT))
    
    # return JsonResponse({'SPState ':cmd})

def controlSmartPlugSD001(cmd):
    json_dict_message = {}
    json_message_data = None
    json_dict_message[constants.ATTR_JSON_MESSAGE_TYPE] = str(constants.ATTR_JSON_MOBILE_STATUS_VALUE)

    json_message_data = { \
        constants.ATTR_JSON_ID_DEVICE : str(constants.ATTR_JSON_ID_SD001_VALUE),\
        constants.ATTR_JSON_NAME_DEVICE : str(constants.ATTR_JSON_NAME_DEVICE_LIGHT_VALUE),\
        constants.ATTR_JSON_RELAY_STATUS_VALUE : str(constants.ATTR_JSON_RELAY_STATUS_VALUE_ACTIVE),\
        constants.ATTR_JSON_ID_ROOM : str(constants.ATTR_JSON_ID_ROOM_R001_VALUE)
    }
     
    if cmd == 'OFFSD001':
        json_message_data[constants.ATTR_JSON_RELAY_STATUS_VALUE] = \
                                    str(constants.ATTR_JSON_RELAY_STATUS_VALUE_UNACTIVE)
    json_dict_message[constants.ATTR_JSON_DATA] = json_message_data
    sock.sendto(json.dumps(json_dict_message).encode('utf-8'), (constants.MESSAGE_RECEIVER_IP,\
                                                        constants.MESSAGE_RECEIVER_PORT))

def controlSmartPlugSD002(cmd):
    json_dict_message = {}
    json_message_data = None
    json_dict_message[constants.ATTR_JSON_MESSAGE_TYPE] = str(constants.ATTR_JSON_MOBILE_STATUS_VALUE)

    json_message_data = { \
        constants.ATTR_JSON_ID_DEVICE : str(constants.ATTR_JSON_ID_SD002_VALUE),\
        constants.ATTR_JSON_NAME_DEVICE : str(constants.ATTR_JSON_NAME_DEVICE_PLUS_VALUE),\
        constants.ATTR_JSON_RELAY_STATUS_VALUE : str(constants.ATTR_JSON_RELAY_STATUS_VALUE_ACTIVE),\
        constants.ATTR_JSON_ID_ROOM : str(constants.ATTR_JSON_ID_ROOM_R001_VALUE)
    }
     
    if cmd == 'OFFSD002':
        json_message_data[constants.ATTR_JSON_RELAY_STATUS_VALUE] = \
                                    str(constants.ATTR_JSON_RELAY_STATUS_VALUE_UNACTIVE)
    json_dict_message[constants.ATTR_JSON_DATA] = json_message_data
    sock.sendto(json.dumps(json_dict_message).encode('utf-8'), (constants.MESSAGE_RECEIVER_IP,\
                                                        constants.MESSAGE_RECEIVER_PORT))


def serverDjango(request):
    cmd = request.GET['cmd']
    print("CMD0: ", cmd)

    # Parse Json
    # jsonStr = json.dumps(cmd)
    # print("json_string 02: " , jsonStr)
    # jsonParse = json.loads(jsonStr)
    # print("parsed_json 02 : " , jsonParse)
    # print("Hang 02: " , jsonParse['MESSAGE_STATUS_VALUE'])

    if cmd == 'ON' or cmd == 'OFF':
        print("CMD1: ", cmd)
        controlSmartPlug(cmd)
        return JsonResponse({'SPState ':cmd})

    # if cmd == 'SEL':
    #     json_dict = selectDevice(cmd)
    #     return JsonResponse({'JSON_SEL':json_dict})

    # if jsonString['ID_DEVICE'] == ATTR_JSON_ID_SD001_VALUE
    #     if jsonString['ELECTRIC_STATUS_VALUE']
    #     print("CMD1: ", cmd)
    #     controlSmartPlug(cmd)
    #     return JsonResponse({'SPState ':cmd})

    if cmd == 'ONSD001' or cmd == 'OFFSD001':
        print("SD001: ", cmd)
        controlSmartPlugSD001(cmd)
        return JsonResponse({'SPState ':cmd})

    if cmd == 'ONSD002' or cmd == 'OFFSD002':
        print("SD002: ", cmd)
        controlSmartPlugSD002(cmd)
        return JsonResponse({'SPState ':cmd})

    if cmd == 'SEL':
        json_dict = selectDevice(cmd)
        return JsonResponse({'JSON_SEL':json_dict})
 


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

