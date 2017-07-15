import json
import socket
import pickle
import MySQLdb
import string
import datetime
import base64

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

def selectListUsers():
    print("Welcome to selectListUsers")
    conn = MySQLdb.connect(host = constants.HOST, user = constants.USER, passwd = constants.PASSWORD, db = constants.DATABASE)
    cur = conn.cursor()
    cur.execute("SELECT userName, email, stateUser, userStyle FROM User;")
    json_array = []
    for r in cur:
        json_dict={
            constants.ATTR_JSON_USER_NAME_IN_USERS : r[0],\
            constants.ATTR_JSON_EMAIL_IN_USERS : r[1],\
            constants.ATTR_JSON_STATE_USER_IN_USERS : r[2],\
            constants.ATTR_JSON_USER_STYLE_IN_USERS : r[3]
        }
        json_array.append(json_dict)
        print(json_array)
    cur.close()
    conn.close()
    return json_array

def selectHistory():
    print("Welcome to selectHistory")
    conn = MySQLdb.connect(host = constants.HOST, user = constants.USER, passwd = constants.PASSWORD, db = constants.DATABASE)
    cur = conn.cursor()
    # query = "SELECT SmartDevice.idSmartDevice, SmartDevice.nameSmartDevice, SmartDevice.stateElectric, SmartDevice.stateRelay" +\
    # "Timer.monthSD, Timer.daySD, Timer.yearSD, Timer.hourSD, Timer.minuteSD, Timer.secondSD" +\
    # "FROM SmartDevice join (Timer join Device_Timer on Timer.idTimer=Device_Timer.idTimer)"+\
    # " on SmartDevice.idSmartDevice = Device_Timer.idSmartDevice"
    cur.execute("""SELECT SmartDevice.idSmartDevice, SmartDevice.nameSmartDevice, Device_Timer.stateElectric, Device_Timer.stateRelay, Timer.monthSD, Timer.daySD, Timer.yearSD, Timer.hourSD, Timer.minuteSD, Timer.secondSD FROM SmartDevice join (Timer join Device_Timer on Timer.idTimer=Device_Timer.idTimer) on SmartDevice.idSmartDevice = Device_Timer.idSmartDevice""")
    json_array = []
    for r in cur:
        json_dict={
            constants.ATTR_JSON_ID_DEVICE : r[0],\
            constants.ATTR_JSON_NAME_DEVICE : r[1],\
            constants.ATTR_JSON_RELAY_STATUS_VALUE : r[3],\
            constants.ATTR_JSON_ELECTRIC_STATUS_VALUE : r[2],\
            constants.ATTR_JSON_MONTHSD : r[4],\
            constants.ATTR_JSON_DAYSD : r[5],\
            constants.ATTR_JSON_YEARSD : r[6],\
            constants.ATTR_JSON_HOURSD : r[7],\
            constants.ATTR_JSON_MINUTESD : r[8],\
            constants.ATTR_JSON_SECONDSD : r[9]
        }
        
        json_array.append(json_dict)
        print("json history: ", json_array)
    cur.close()
    conn.close()
    return json_array

def loginUser(cmd, json_user_name, json_password):
    print("welcome login")
    if cmd == 'LOGIN_DEVICE':
        print("welcome login 01")
        conn = MySQLdb.connect(host = constants.HOST, user = constants.USER, passwd = constants.PASSWORD, db = constants.DATABASE)
        print("welcome login 02")
        cur = conn.cursor()
        print("welcome login 03")
        cur.execute("SELECT userName, password, stateUser, userStyle FROM User")
        json_dict = {}
        for r in cur:
            # print("password chua ma hoa", r[1])
            passdecode = base64.b64decode(r[1])
            # print("password chua ma hoa 02", passdecode)
            passdecode = passdecode.decode('utf-8')
            # print("decode password ", passdecode)

            # print("json_password 01: ", json_password)
            # json_password = bytes(json_password, 'utf-8')
            # print("json_password 02: ", json_password)
            # json_password = base64.b64encode(json_password)
            # print("json_password 03: ", json_password)

            if r[0] == json_user_name and passdecode == json_password:
                if r[2] == 1:
                    print("json_user_name success ", json_user_name)
                    print("json_password success", json_password)
                    print("r[0] success ", r[0])
                    print("r[1] success", passdecode)
                    print("r[2] success", r[2])
                    if r[3] == 1:
                        print("r[3] success admin: ", r[3])
                        json_dict = { constants.ATTR_JSON_MESSAGE_TYPE: constants.ATTR_JSON_LOGIN_SUCCESSFUL_ADMIN}
                        print("json_dict ", json_dict)
                        cur.close()
                        conn.close()
                        return json_dict
                    elif r[3] == 0:
                        print("r[3] success user: ", r[3])
                        json_dict = { constants.ATTR_JSON_MESSAGE_TYPE: constants.ATTR_JSON_LOGIN_SUCCESSFUL_USER}
                        print("json_dict ", json_dict)
                        cur.close()
                        conn.close()                        
                        return json_dict
                    else:
                        print("userStyle error")
                elif r[2] == 0:
                    print("json_user_name unactive ", json_user_name)
                    print("json_password unactive", json_password)
                    print("r[0] unactive ", r[0])
                    print("r[1] unactive ", r[1])
                    print("r[2] unactive ", r[2])
                    json_dict = { constants.ATTR_JSON_MESSAGE_TYPE: constants.ATTR_JSON_LOGIN_ERROR_UNACTIVE}
                    print("json_dict ", json_dict)
                    cur.close()
                    conn.close()
                    return json_dict
                # return json_dict
            else:
                print("json_user_name error", json_user_name)
                print("json_password error", json_password)
                print("r[0] error ", r[0])
                print("r[1] error", r[1])
                json_dict = { constants.ATTR_JSON_MESSAGE_TYPE: constants.ATTR_JSON_LOGIN_ERROR}
                print("json_dict ", json_dict)
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

    print("json_password 01: ", json_password)
    json_password = bytes(json_password, 'utf-8')
    print("json_password 02: ", json_password)
    json_password = base64.b64encode(json_password)
    print("json_password 03: ", json_password)

    if b_username == False: 
        if b_email == False:
            iduser = autoIDUser()
            print("ID USER 02: " + iduser)
            conn = MySQLdb.connect(host = constants.HOST, user = constants.USER, passwd = constants.PASSWORD, db = constants.DATABASE)
            cur = conn.cursor()
            print("db 02")
            try: 
                cur.execute("INSERT INTO User VALUES (%s,%s,%s,%s,%s,%s)", \
                                    (iduser, json_user_name, json_password, json_email, 0, 0))
                print("db 03")
                conn.commit()
                json_dict_register = {constants.ATTR_JSON_MESSAGE_TYPE: \
                                            constants.ATTR_JSON_REGISTER_SUCCESSFUL}
                print("Register Successful: " , json_dict_register)
            except:
                conn.rollback()
                json_dict_register = {constants.ATTR_JSON_MESSAGE_TYPE: \
                                            constants.ATTR_JSON_REGISTER_ERROR}
                print("Register error: " , json_dict_register)
            conn.close()
        else:
            json_dict_register = {constants.ATTR_JSON_MESSAGE_TYPE: \
                                            constants.ATTR_JSON_REGISTER_EMAIL_EXIST}
            print("Email exist " , json_dict_register)
    else:
        json_dict_register = {constants.ATTR_JSON_MESSAGE_TYPE: \
                                            constants.ATTR_JSON_REGISTER_USERNAME_EXIST}
        print("Username exist" , json_dict_register)  
    return json_dict_register      

def updateStateUser(json_user_name, json_status_users):
    json_dict_update = {}
    conn = MySQLdb.connect(host = constants.HOST, user = constants.USER, passwd = constants.PASSWORD, db = constants.DATABASE)
    cur = conn.cursor()
    try: 
        cur.execute("""UPDATE SMARTDEVICE.User SET stateUser = %s WHERE userName = %s;""",\
                                            (json_status_users,json_user_name))
        print("db 03")
        conn.commit()
        json_dict_update = {constants.ATTR_JSON_MESSAGE_TYPE: \
                                    constants.ATTR_JSON_UPDATE_SUCCESSFUL_STATE_USER}
        print("updateStateUser Successful: " , json_dict_update)
    except:
        conn.rollback()
        json_dict_update = {constants.ATTR_JSON_MESSAGE_TYPE: \
                                    constants.ATTR_JSON_UPDATE_ERROR_STATE_USER}
        print("updateStateUser error: " , json_dict_update)
    conn.close()
    return json_dict_update

def updateUserStyle(json_user_name, json_users_style):
    json_dict_update ={}
    conn = MySQLdb.connect(host = constants.HOST, user = constants.USER, passwd = constants.PASSWORD, db = constants.DATABASE)
    cur = conn.cursor()
    try: 
        cur.execute("""UPDATE SMARTDEVICE.User SET userStyle = %s WHERE userName = %s;""",\
                                            (json_users_style, json_user_name))
        print("db 03")
        conn.commit()
        json_dict_update = {constants.ATTR_JSON_MESSAGE_TYPE: \
                                    constants.ATTR_JSON_UPDATE_SUCCESSFUL_USER_STYLE}
        print("updateUserStyle Successful: " , json_dict_update)
    except:
        conn.rollback()
        json_dict_update = {constants.ATTR_JSON_MESSAGE_TYPE: \
                                    constants.ATTR_JSON_UPDATE_ERROR_USER_STYLE}
        print("updateUserStyle error: " , json_dict_update)
    conn.close()
    return json_dict_update

def deleteUser(json_user_name):
    json_dict_delete ={}
    conn = MySQLdb.connect(host = constants.HOST, user = constants.USER, passwd = constants.PASSWORD, db = constants.DATABASE)
    cur = conn.cursor()
    try:
        cur.execute("""DELETE FROM SMARTDEVICE.User WHERE userName = %s;""", (json_user_name,))
        conn.commit()
        json_dict_delete = {constants.ATTR_JSON_MESSAGE_TYPE: \
                                    constants.ATTR_JSON_DELETE_STATUS_VALUE_USER_SUCCESSFUL}
        print("deleteUser Successful: " , json_dict_delete)
    except:
        conn.rollback()
        json_dict_delete = {constants.ATTR_JSON_MESSAGE_TYPE: \
                                    constants.ATTR_JSON_DELETE_STATUS_VALUE_USER_ERROR}
        print("deleteUser error: " , json_dict_update)
    conn.close()
    return json_dict_delete

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

"""Trang Modified"""
def insertRoom(cmd, json_idRoom, json_nameRoom):
    json_dict_insert={}
    conn = MySQLdb.connect(host = constants.HOST, user = constants.USER, passwd = constants.PASSWORD, db = constants.DATABASE)
    cur = conn.cursor()
    try:
        cur.execute("""INSERT INTO SMARTDEVICE.Room(idRoom, nameRoom) VALUES('%s', '%s');""" \
                                                                 (json_idRoom, json_nameRoom))
        conn.commit()
        json_dict_insert = {constants.ATTR_JSON_MESSAGE_TYPE: \
                                    constants.ATTR_JSON_INSERT_ROOM_SUCCESSFUL}
        print("insertRoom Successful: " , json_dict_insert)
    except:
        conn.rollback()
        json_dict_insert = {constants.ATTR_JSON_MESSAGE_TYPE: \
                                    constants.ATTR_JSON_INSERT_ROOM_ERROR}
        print("insertRoom error: " , json_dict_insert)
    conn.close()
    return json_dict_insert

"""Trang Modified"""
def deleteRoom(cmd, json_idRoom):
    json_dict_delete={}
    conn = MySQLdb.connect(host = constants.HOST, user = constants.USER, passwd = constants.PASSWORD, db = constants.DATABASE)
    cur = conn.cursor()
    try:
        cur.execute("""DELETE FROM SMARTDEVICE.Room WHERE idRoom = %s;""", (json_idRoom,))
        conn.commit()
        json_dict_delete = {constants.ATTR_JSON_MESSAGE_TYPE: \
                                    constants.ATTR_JSON_DELETE_ROOM_SUCCESSFUL}
        print("deleteRoom Successful: " , json_dict_delete)
    except:
        conn.rollback()
        json_dict_delete = {constants.ATTR_JSON_MESSAGE_TYPE: \
                                    constants.ATTR_JSON_DELETE_ROOM_ERROR}
        print("deleteRoom error: " , json_dict_delete)
    conn.close()

"""Trang Modified"""
def selectRoom():
    print("Welcome to selectRoom")
    conn = MySQLdb.connect(host = constants.HOST, user = constants.USER, passwd = constants.PASSWORD, db = constants.DATABASE)
    cur = conn.cursor()

    cur.execute("""SELECT idRoom, nameRoom FROM Room""")
    json_array = []
    for r in cur:
        json_dict={
            constants.ATTR_JSON_ID_ROOM : r[0],\
            constants.ATTR_JSON_NAME_ROOM : r[1],\
        }
        
        json_array.append(json_dict)
        print("json history: ", json_array)
    cur.close()
    conn.close()
    return json_array

def serverDjango(request):
    cmd = request.GET['cmd']
    print("CMD0: ", cmd)

    json_parse = json.loads(cmd)
    # print("parsed_json : " , json_parse)

    json_mes = str(json_parse['MESSAGE_STATUS_VALUE'])
    print("json_mes : " , json_mes)

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

    elif json_mes == 'SELECT_LIST_USERS':
        json_select_users = selectListUsers()
        print("Select list users: ", json_mes)
        json_dict = {constants.ATTR_JSON_MESSAGE_TYPE: \
                            constants.ATTR_JSON_MESSAGE_STATUS_VALUE_SELECT_LIST_USERS, \
                        'SEL_USERS' : json_select_users }
        # return JsonResponse({ 'SEL_USERS' : json_select_users })
        return JsonResponse(json_dict)

    elif json_mes == 'SELECT_HISTORY':
        json_history = selectHistory()
        print("SELECT_HISTORY: ", json_mes)
        json_dict = {constants.ATTR_JSON_STATUS_VALUE_SELECT_HISTORY: json_history}
        return JsonResponse(json_dict)

    elif json_mes == 'STATE_USERS_ACTIVE_UNACTIVE':
        print("STATE_USERS_ACTIVE_UNACTIVE: ", json_mes)
        json_user_name = str(json_parse['USER_NAME'])
        # modified @ July 5th
        json_status_users = int(json_parse['USER_STATUS_VALUE'])
        json_dict_state = updateStateUser(json_user_name, json_status_users)
        print("Hang 01", json_dict_state)
        return JsonResponse(json_dict_state)

    elif json_mes == 'USER_STYLE_ACTIVE_UNACTIVE':
        print("USER_STYLE_ACTIVE_UNACTIVE: ", json_mes)
        json_user_name = str(json_parse['USER_NAME'])
        json_users_style = int(json_parse['USER_STYLE_STATUS_VALUE'])
        json_dict_style = updateUserStyle(json_user_name, json_users_style)
        print("Hang 02", json_dict_style)
        return JsonResponse(json_dict_style)

    elif json_mes == "DELETE_USER":
        json_user_name = str(json_parse['USER_NAME'])
        print("json_user_name", json_user_name)
        json_delete = deleteUser(json_user_name)
        return JsonResponse(json_delete)

    elif json_mes == 'INSERT_ROOM':
        json_idRoom = str(json_parse['ROOM_USER'])
        json_nameRoom = str(json_parse['NAME_ROOM'])
        print("json_idRoom", json_idRoom)
        print("json_nameRoom", json_nameRoom)
        json_insert_room = insertRoom(json_idRoom, json_nameRoom)
        return JsonResponse(json_insert_room)

    elif json_mes = 'DELETE_ROOM':
        json_idRoom = str(json_parse['ROOM_USER'])
        print("json_idRoom", json_idRoom)
        json_delete_room = deleteRoom(json_idRoom)
        return JsonResponse(json_delete_room)

    elif json_mes = 'SELECT_ROOM':
        json_room = selectRoom()
        print("SELECT_ROOM: ", json_mes)
        json_dict = {constants.ATTR_JSON_SELECT_ROOM: json_room}
        return JsonResponse(json_dict)