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

import time

from ctimer import Timer
from deviceTimer import DeviceTimer
from smartDevice import SmartDevice

import optionParser

from cffi_interfaces.__cffi_jsonCommon import jsonCommon_cffi
from cffi_interfaces.__cffi_jsonCommon import jsonCommon_c

from cffi_interfaces.__cffi_jsonParser import jsonParser_cffi
from cffi_interfaces.__cffi_jsonParser import jsonParser_c

from cffi_interfaces.__cffi_jsonBuilder import jsonBuilder_cffi
from cffi_interfaces.__cffi_jsonBuilder import jsonBuilder_c

from cffi_interfaces.__cffi_messageSender import messageSender_cffi
from cffi_interfaces.__cffi_messageSender import messageSender_c

import message_handler

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

        info.deviceTimer.idTimer = deviceTimer.idTimer
        info.deviceTimer.idSmartDevice = deviceTimer.idSmartDevice
        info.deviceTimer.stateElectric = deviceTimer.stateElectric
        info.deviceTimer.stateRelay = deviceTimer.stateRelay

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
        smartplug = SmartDevice("SD001", "192.168.0.103:5600", \
                                                        "R0001", mylist)
        smartlight = SmartDevice("SD002", "192.168.0.104:5600", \
                                                        "R0001", mylist)
        
        while True:
            topic = self.sock.recv(2, zmq.NOBLOCK)
            message = self.sock.recv(2, zmq.NOBLOCK)
            print("message ",message)
            message_processor = message_handler.MessageHandler(topic, message) 
            message_processor.run()
            time.sleep(1)
 
        self.sock.close()

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
