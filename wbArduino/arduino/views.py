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
    print("Hang 04")
    if cmd == 'SELECT_DEVICE':
        print("Hang 05")
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

def controlSmartPlug(cmd,json_id_device,json_name_device):
    # # cmd = request.GET['cmd']
    # print("CMD2: ", cmd)
    # if cmd == '1':
    #     json_dict_on = { 
    #         constants.ATTR_JSON_MESSAGE_TYPE : constants.ATTR_JSON_MOBILE_STATUS_VALUE, \
    #         constants.ATTR_JSON_DATA : { \
    #             constants.ATTR_JSON_ID_DEVICE : json_id_device,\
    #             constants.ATTR_JSON_NAME_DEVICE : "DEVICE_LIGHT",\
    #             constants.ATTR_JSON_RELAY_STATUS_VALUE : constants.ATTR_JSON_RELAY_STATUS_VALUE_ACTIVE,\
    #             constants.ATTR_JSON_ID_ROOM : "R001"
    #         }
    #     }
    #     print("CMD ON: ", json_dict_on) 
    #     sock.sendto(json.dumps(json_dict_on).encode(), (MESSAGE_RECEIVER_IP, MESSAGE_RECEIVER_PORT))
        
    # elif cmd == '0':
    #     json_dict_off = { 
    #         constants.ATTR_JSON_MESSAGE_TYPE : constants.ATTR_JSON_MOBILE_STATUS_VALUE, \
    #         constants.ATTR_JSON_DATA : { \
    #             constants.ATTR_JSON_ID_DEVICE : json_id_device,\
    #             constants.ATTR_JSON_NAME_DEVICE : "DEVICE_LIGHT",\
    #             constants.ATTR_JSON_RELAY_STATUS_VALUE : constants.ATTR_JSON_RELAY_STATUS_VALUE_UNACTIVE,\
    #             constants.ATTR_JSON_ID_ROOM : "R001"
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
        constants.ATTR_JSON_ID_DEVICE : str(json_id_device),\
        constants.ATTR_JSON_NAME_DEVICE : str(json_name_device),\
        constants.ATTR_JSON_RELAY_STATUS_VALUE : str(constants.ATTR_JSON_RELAY_STATUS_VALUE_ACTIVE),\
        constants.ATTR_JSON_ID_ROOM : str(constants.ATTR_JSON_ID_ROOM_R001_VALUE)
    }


     
    if cmd == '0':
        json_message_data[constants.ATTR_JSON_RELAY_STATUS_VALUE] = \
                                    str(constants.ATTR_JSON_RELAY_STATUS_VALUE_UNACTIVE)
    json_dict_message[constants.ATTR_JSON_DATA] = json_message_data

    print("json_dict_message" , json_dict_message)
    sock.sendto(json.dumps(json_dict_message).encode('utf-8'), (constants.MESSAGE_RECEIVER_IP,\
                                                        constants.MESSAGE_RECEIVER_PORT))


def serverDjango(request):
    cmd = request.GET['cmd']
    print("CMD0: ", cmd)

    json_parse = json.loads(cmd)
    print("parsed_json : " , json_parse)

    json_mes = str(json_parse['MESSAGE_STATUS_VALUE'])

    if json_mes == 'SELECT_DEVICE':
        print("Hang 03:", json_mes)
        json_dict = selectDevice(json_mes)
        return JsonResponse({ 'JSON_SEL' : json_dict })

    elif json_mes == 'ON_OFF_DEVICE':
        print("Hang 04" , json_mes)
        json_id_device = str(json_parse['ID_DEVICE'])
        json_name_device = str(json_parse['NAME_DEVICE'])
        json_status_device = str(json_parse['ELECTRIC_STATUS_VALUE'])

        print("json_id_device: " , json_id_device)
        print("json_name_device: " , json_name_device)
        print("json_status_device: " , json_status_device)

        controlSmartPlug(json_status_device,json_id_device,json_name_device)
        return JsonResponse({'SPState ': json_status_device})



 


