import json
import socket
import pickle
import MySQLdb
import string
import datetime

from arduino import constants

from django.shortcuts import render
from django.http import JsonResponse

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Create your views here.
def arduino(request):
    return render(request, "arduino.html", {})

def selectDevice(cmd):
    print("Hang 01")
    if cmd == 'SELECT_DEVICE':
        # print("Hang 02")
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

def loginUser(cmd, json_user_name, json_password):
    if cmd == 'LOGIN_DEVICE':
        conn = MySQLdb.connect(host = constants.HOST, user = constants.USER, passwd = constants.PASSWORD, db = constants.DATABASE)
        cur = conn.cursor()
        cur.execute("SELECT userName, password, stateUser FROM User")
        json_dict = {}
        for r in cur:
            if r[0] == json_user_name and r[1] == json_password:
                if r[2] == 'ACTIVE':
                    print("json_user_name success ", json_user_name)
                    print("json_password success", json_password)
                    print("r[0] success ", r[0])
                    print("r[1] success", r[1])
                    print("r[2] sucess", r[2])
                    json_dict = { constants.ATTR_JSON_MESSAGE_TYPE: constants.ATTR_JSON_LOGIN_SUCCESSFUL}
                elif r[2] == 'UNACTIVE':
                    json_dict = { constants.ATTR_JSON_MESSAGE_TYPE: constants.ATTR_JSON_LOGIN_ERROR_UNACTIVE}
                print("USER ACTIVE UNACTIVE", json_dict)
                return json_dict
            else:
                print("json_user_name error", json_user_name)
                print("json_password error", json_password)
                print("r[0] error ", r[0])
                print("r[1] error", r[1])
                json_dict = { constants.ATTR_JSON_MESSAGE_TYPE: constants.ATTR_JSON_LOGIN_ERROR}
        cur.close()
        conn.close()
        return json_dict

def existUsername(json_user_name):
    conn = MySQLdb.connect(host = constants.HOST, user = constants.USER, passwd = constants.PASSWORD, db = constants.DATABASE)
    cur = conn.cursor()
    cur.execute("SELECT userName FROM User")
    for r in cur:
        if r[0] == json_user_name:
            return True
    cur.close()
    conn.close()
    return False

def existEmail(json_email):
    conn = MySQLdb.connect(host = constants.HOST, user = constants.USER, passwd = constants.PASSWORD, db = constants.DATABASE)
    cur = conn.cursor()
    cur.execute("SELECT email FROM User")
    for r in cur:
        if r[0] == json_email:
            return True
    cur.close()
    conn.close()
    return False

def autoIDUser():
    iduser = 'US'

    date_time = datetime.datetime.now()

    year_auto = str(date_time.year)

    month_auto = str(date_time.month)
    if len(month_auto) == 1:
        month_auto = '0' + month_auto

    day_auto = str(date_time.day)
    if len(day_auto) == 1:
        day_auto = '0' + day_auto

    hour_auto = str(date_time.hour)
    if len(hour_auto) == 1:
        hour_auto = '0' + hour_auto

    minute_auto = str(date_time.minute)
    if len(minute_auto) == 1:
        minute_auto = '0' + minute_auto

    second_auto = str(date_time.second)
    if len(second_auto) == 1:
        second_auto = '0' + second_auto

    iduser = iduser + year_auto + month_auto + day_auto + hour_auto + minute_auto + second_auto
    print("ID USER 01: " , iduser)

    return iduser

def registerUser(json_user_name, json_password, json_email):
    json_dict_register = {}
    b_username = existUsername(json_user_name)
    b_email = existEmail(json_email)
    print("b_username: ", b_username)
    print("b_email: ", b_email)

    if b_username == False: 
        if b_email == False:
            iduser = autoIDUser()
            print("ID USER 02: " + iduser)
            conn = MySQLdb.connect(host = constants.HOST, user = constants.USER, passwd = constants.PASSWORD, db = constants.DATABASE)
            cur = conn.cursor()
            print("db 02")
            try: 
                cur.execute("INSERT INTO User VALUES (%s,%s,%s,%s,%s,%s)", (iduser, json_user_name, json_password, json_email, 'UNACTIVE', 0))
                print("db 03")
                conn.commit()
                json_dict_register = {constants.ATTR_JSON_MESSAGE_TYPE: constants.ATTR_JSON_REGISTER_SUCCESSFUL}
                print("Register Successful: " , json_dict_register)
            except:
                conn.rollback()
                json_dict_register = {constants.ATTR_JSON_MESSAGE_TYPE: constants.ATTR_JSON_REGISTER_ERROR}
                print("Register error: " , json_dict_register)
            conn.close()
        else:
            json_dict_register = {constants.ATTR_JSON_MESSAGE_TYPE: constants.ATTR_JSON_REGISTER_EMAIL_EXIST}
            print("Email exist " , json_dict_register)
    else:
        json_dict_register = {constants.ATTR_JSON_MESSAGE_TYPE: constants.ATTR_JSON_REGISTER_USERNAME_EXIST}
        print("Username exist" , json_dict_register)  
    return json_dict_register      


def controlSmartPlug(cmd,json_id_device,json_name_device):
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
        print("SELECT_DEVICE:", json_mes)
        json_dict = selectDevice(json_mes)
        return JsonResponse({ 'JSON_SEL' : json_dict })

    elif json_mes == 'ON_OFF_DEVICE':
        print("ON_OFF_DEVICE " , json_mes)
        json_id_device = str(json_parse['ID_DEVICE'])
        json_name_device = str(json_parse['NAME_DEVICE'])
        json_status_device = str(json_parse['ELECTRIC_STATUS_VALUE'])

        print("json_id_device: " , json_id_device)
        print("json_name_device: " , json_name_device)
        print("json_status_device: " , json_status_device)

        controlSmartPlug(json_status_device,json_id_device,json_name_device)
        return JsonResponse({'SPState ': json_status_device})

    elif json_mes =='LOGIN_DEVICE':
        print("Login: " , json_mes)

        json_user_name = str(json_parse['USER_NAME'])
        json_password = str(json_parse['PASSWORD'])

        json_dict_login = loginUser(json_mes, json_user_name, json_password)
        print("json_dict_login: " , json_dict_login)

        return JsonResponse(json_dict_login)

    elif json_mes == 'REGISTER_DEVICE':
        print("Register: " , json_mes)

        json_user_name = str(json_parse['USER_NAME'])
        print("1: " , json_user_name)
        json_password = str(json_parse['PASSWORD'])
        print("2: " , json_password)
        json_email = str(json_parse['EMAIL'])
        print("3: " , json_email)

        json_dict_register = registerUser(json_user_name, json_password, json_email)
        print("4: "  , json_dict_register)
        return JsonResponse(json_dict_register)