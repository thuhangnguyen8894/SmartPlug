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

    def insert_to_table_Timer_ForC(self, ctimer):
        info = DBSmartDevice_cffi.new("SmartDeviceInfo* ");

        info.timer.idTimer = ctimer.idTimer
        info.timer.monthSD = ctimer.monthSD
        info.timer.daySD = ctimer.daySD
        info.timer.yearSD = ctimer.yearSD
        info.timer.hourSD = ctimer.hourSD
        info.timer.minSD = ctimer.minuteSD
        info.timer.secSD = ctimer.secondSD

        print("insert table Timer")
        print("idTimer: ", info.timer.idTimer)
        print("monthSD: ", info.timer.monthSD)

        DBSmartDevice_c.insert_to_table_Timer_ForC(info);

    def insert_to_table_Device_Timer_ForC(self, cdevice_timer):
        info = DBSmartDevice_cffi.new("SmartDeviceInfo* ");

        info.device_timer.idTimer = cdevice_timer.idTimer
        info.device_timer.idSmartDevice = cdevice_timer.idSmartDevice
        info.device_timer.stateElectric = cdevice_timer.stateElectric
        info.device_timer.stateRelay = cdevice_timer.stateRelay

        print("insert table Device_Timer")
        print("idTimer: ", info.device_timer.idTimer)
        print("idSmartDevice: ", info.device_timer.idSmartDevice)
        print("stateElectric: ", info.device_timer.stateElectric)
        print("stateRelay: ", info.device_timer.stateRelay)

        DBSmartDevice_c.insert_to_table_Device_Timer_ForC(info);
        

    def select_idTimer_to_table_Timer_ForC(self, ctimer):
        info = DBSmartDevice_cffi.new("SmartDeviceInfo* ");

        print("select table Timer, step 1:")
        print("ctimer.idTimer: ", ctimer.idTimer)

        info.timer.idTimer = ctimer.idTimer
        print("select table Timer, step 2:")
        print("info.timer.idTimer: ", info.timer.idTimer)

        DBSmartDevice_c.select_idTimer_to_table_Timer_ForC(info);

        print("select table Timer, step 2:") 
        return DBSmartDevice_cffi.string(info[0].timer.idTimer)
        print("select table Timer")


    def run(self):
        print("Processor run on %s:%s" %(self.host, self.port))

        mylist = []
        smartplug = SmartDevice("SD001", "192.168.0.103:5600", "R0001", mylist)
        smartlight = SmartDevice("SD002", "192.168.0.104:5600", "R0001", mylist)
        
        while True:
            topic = self.sock.recv()
            message = self.sock.recv()
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

            idTimer_insert_list = self.select_idTimer_to_table_Timer_ForC(ctimer)
            print("idTimer_insert_list: ", idTimer_insert_list)

            print("ip_port: ", ip_port)
            print("smartplug.ip_port: ", smartplug.ip_port)

            if smartplug.ip_port == ip_port.decode(encoding = "utf-8"):
                smartplug.addEmplementIdTimer(idTimer_insert_list)
                lenListIdTimer = len(smartplug.listIdTimer)
                print("+------PLUG insert idTimer-------+")
                for x in range(lenListIdTimer):
                    print("Plug[", x, "] :", smartplug.listIdTimer[x])
            elif smartlight.ip_port == ip_port.decode(encoding = "utf-8"):
                smartlight.addEmplementIdTimer(idTimer_insert_list)
                lenListIdTimer = len(smartlight.listIdTimer)
                print("+------LIGHT insert idTimer-------+")
                for x in range(lenListIdTimer):
                    print("Light[", x, "] :", smartlight.listIdTimer[x])
            else:
                print("DON'T EXIT")

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