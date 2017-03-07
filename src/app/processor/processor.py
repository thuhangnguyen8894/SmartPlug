"""
File: processor.py
=========================

Copyright (c) Tien Nguyen Anh

Modified History
----------------
2016-Dec-19 Created tien.nguyenanh94@gmail.com
2017-Jan-18 Modified tn-trang.tran@outlook.com
2017-Jan-19 Modified thuhang.nguyen8894@gmail.com
2017-Feb-18 Modified tn-trang.tran@outlook.com
2017-Mar-07 Modified tn-trang.tran@outlook.com
"""

import sys
import threading
import zmq

from ctimer import Timer
from cdevice_timer import Device_Timer
from csmartdevice import SmartDevice

import optionParser

from cffi_interfaces.__cffi_jsonCommon_smart_device_status_value import jsonCommon_smart_device_status_value_cffi
from cffi_interfaces.__cffi_jsonCommon_smart_device_status_value import jsonCommon_smart_device_status_value_c

from cffi_interfaces.__cffi_jsonParser_smart_device_status_value import jsonParser_smart_device_status_value_cffi
from cffi_interfaces.__cffi_jsonParser_smart_device_status_value import jsonParser_smart_device_status_value_c

from cffi_interfaces.__cffi_jsonBuilder_smart_device_status_value import jsonBuilder_smart_device_status_value_cffi
from cffi_interfaces.__cffi_jsonBuilder_smart_device_status_value import jsonBuilder_smart_device_status_value_c

from cffi_interfaces.__cffi_messageSender import messageSender_cffi
from cffi_interfaces.__cffi_messageSender import messageSender_c

from cffi_interfaces.__cffi_DBSmartDevice import DBSmartDevice_cffi
from cffi_interfaces.__cffi_DBSmartDevice import DBSmartDevice_c 

class Processor(threading.Thread):
    def __init__(self, host, port, topic=None):
        threading.Thread.__init__(self)
        self.host = host 
        self.port = port
        self.topic = topic
        self.context = zmq.Context()
        self.sock = self.context.socket(zmq.SUB)

        if topic != None:
            for item in self.topic:
                self.sock.setsockopt_string(zmq.SUBSCRIBE, item)


    def connect(self):
        cmd = "tcp://" + self.host
        cmd = cmd + ":"
        cmd = cmd + self.port
        self.sock.connect(cmd)


    def subscribeTopic(self, topic):

        if self.topic == None:
            self.topic = topic
        else:    
            self.topic + topic

        for item in topic:
            self.sock.setsockopt_string(zmq.SUBSCRIBE, item)  

    
    '''
       Function parsert infomation of SmartDevice
    '''
    def parseDataSmartDeviceJsonForC(self, jsonMessage):
        info = jsonParser_smart_device_status_value_cffi.new("SmartDeviceInfo* ");
        
        jsonParser_smart_device_status_value_c.parseDataSmartDeviceJsonForC(jsonMessage, info);      

        return jsonParser_smart_device_status_value_cffi.string(info[0].device_timer.idSmartDevice), \
                jsonParser_smart_device_status_value_cffi.string(info[0].device_timer.stateRelay), \
                jsonParser_smart_device_status_value_cffi.string(info[0].device_timer.stateElectric), \
                jsonParser_smart_device_status_value_cffi.string(info[0].device.ip_port), \
                jsonParser_smart_device_status_value_cffi.string(info[0].device.idRoom), \
                jsonParser_smart_device_status_value_cffi.string(info[0].timer.idTimer), \
                jsonParser_smart_device_status_value_cffi.string(info[0].sender.ip), \
                info[0].sender.port, \
                info[0].timer.monthSD, \
                info[0].timer.daySD, \
                info[0].timer.yearSD, \
                info[0].timer.hourSD, \
                info[0].timer.minSD, \
                info[0].timer.secSD

    
    def buildJsonMessage(self, message):
        pass

    
    def sendMessageToArduino(self, message, host, port):
        messageStr = messageSender_cffi.new("char *")
        host = messageSender_cffi.new("char *")
        messageStr[0] = message
        host[0] = host

        messageSender_c.sendMessageUDPForC(messageStr, host, port)

    
    '''
       Function insert data to table Timer
    '''
    def insert_to_table_Timer_ForC(self, ctimer):
        info = DBSmartDevice_cffi.new("SmartDeviceInfo* ");

        info.timer.idTimer = ctimer.idTimer
        info.timer.monthSD = ctimer.monthSD
        info.timer.daySD = ctimer.daySD
        info.timer.yearSD = ctimer.yearSD
        info.timer.hourSD = ctimer.hourSD
        info.timer.minSD = ctimer.minuteSD
        info.timer.secSD = ctimer.secondSD

        DBSmartDevice_c.insert_to_table_Timer_ForC(info);

    
    '''
       Function insert data to table Device_Timer
    '''
    def insert_to_table_Device_Timer_ForC(self, cdevice_timer):
        info = DBSmartDevice_cffi.new("SmartDeviceInfo* ");

        info.device_timer.idTimer = cdevice_timer.idTimer
        info.device_timer.idSmartDevice = cdevice_timer.idSmartDevice
        info.device_timer.stateElectric = cdevice_timer.stateElectric
        info.device_timer.stateRelay = cdevice_timer.stateRelay

        DBSmartDevice_c.insert_to_table_Device_Timer_ForC(info);

    
    '''
       Function select idTimer from table Timer
    '''
    def select_idTimer_to_table_Timer_ForC(self, ctimer):
        info = DBSmartDevice_cffi.new("SmartDeviceInfo* ");
        info.timer.idTimer = ctimer.idTimer

        DBSmartDevice_c.select_idTimer_to_table_Timer_ForC(info);
        return DBSmartDevice_cffi.string(info[0].timer.idTimer)


    '''
       Function append idTimer to list of class csmartdevice
    '''
    def append_emplement_to_list_idTimer_of_csmartdevice(self, smartplug, smartlight, ip_port, idTimer):
        ip_port_decode = ip_port.decode(encoding = "utf-8")

        if smartplug.ip_port == ip_port_decode:
            smartplug.addEmplementIdTimer(idTimer)
            lenListIdTimer = len(smartplug.listIdTimer)
            print("------PLUG insert idTimer------")
            for x in range(lenListIdTimer):
                print("Plug[", x, "] :", smartplug.listIdTimer[x])

        elif smartlight.ip_port == ip_port_decode:
            smartlight.addEmplementIdTimer(idTimer)
            lenListIdTimer = len(smartlight.listIdTimer)
            print("------LIGHT insert idTimer------")
            for x in range(lenListIdTimer):
                print("Light[", x, "] :", smartlight.listIdTimer[x])

        else:
            print("DEVEICE NOT EXIST")

    
    '''
       Function run
    '''
    def run(self):
        print("Processor run on %s:%s" %(self.host, self.port))

        mylist = []
        smartplug = SmartDevice("SD001", "192.168.0.103:5600", "R0001", mylist)
        smartlight = SmartDevice("SD002", "192.168.0.104:5600", "R0001", mylist)
        
        while True:
            topic = self.sock.recv(2)
            message = self.sock.recv(2)
            print("message ",message)
            
            idSmartDevice, stateRelay, stateElectric, ip_port, \
            idRoom, idTimer, ip, port, monthSD, daySD, yearSD, hourSD, \
            minSD, secSD = self.parseDataSmartDeviceJsonForC(message)

            print("idSmartDevice: ", idSmartDevice)
            print("stateRelay: ", stateRelay)
            print("stateElectric: ", stateElectric)
            print("ip_port: ", ip_port)
            print("idRoom: ", idRoom)
            print("idTimer: ", idTimer)
            print("ip: ", ip)
            print("port: ", port)
            print("Date: " , monthSD, "/" , daySD, "/" , yearSD)
            print("Time: " , hourSD, ":" , minSD, ":" , secSD)

            ctimer = Timer(idTimer, daySD, monthSD, yearSD, 
                                                 hourSD, minSD, secSD)

            cdevice_timer = Device_Timer(idTimer, idSmartDevice, 
                                            stateElectric, stateRelay)

            self.insert_to_table_Timer_ForC(ctimer)
            self.insert_to_table_Device_Timer_ForC(cdevice_timer)

            idTimer_insert_csmartdevice = self.select_idTimer_to_table_Timer_ForC(ctimer)

            self.append_emplement_to_list_idTimer_of_csmartdevice(smartplug, smartlight, \
                                                    ip_port, idTimer_insert_csmartdevice)


'''
    Main
'''
if __name__ == '__main__':

    if len(sys.argv) < 4:
        print("Please provide at least 3 arguments.")
        sys.exit(2)

    host, port, topic = optionParser.parseCmdLineArg(sys.argv)    

    processor = Processor(host, port, topic)

    processor.connect()
    
    try:
        processor.run()
    except KeyboardInterrupt:
        print("Keyboard Interruption Errors.")