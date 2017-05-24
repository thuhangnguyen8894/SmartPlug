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
2017-May-07 Modified tn-trang.tran@outlook.com
"""

import sys
import threading
import zmq

import time

from timer import Timer
from deviceTimer import DeviceTimer
from smartDevice import SmartDevice

import optionParser
import message_handler

from cffi_interfaces.__cffi_jsonCommon import jsonCommon_cffi
from cffi_interfaces.__cffi_jsonCommon import jsonCommon_c

from cffi_interfaces.__cffi_jsonParser import jsonParser_cffi
from cffi_interfaces.__cffi_jsonParser import jsonParser_c

from cffi_interfaces.__cffi_jsonBuilder import jsonBuilder_cffi
from cffi_interfaces.__cffi_jsonBuilder import jsonBuilder_c

from cffi_interfaces.__cffi_messageSender import messageSender_cffi
from cffi_interfaces.__cffi_messageSender import messageSender_c

class Processor(threading.Thread):
    def __init__(self, host, port, topic=None):
        threading.Thread.__init__(self)
        self.host = host 
        self.port = port
        self.topic = topic
        self.context = zmq.Context()
        self.sock = self.context.socket(zmq.PAIR)


    def connect(self):
        cmd = "tcp://" + self.host
        cmd = cmd + ":"
        cmd = cmd + self.port
        print("cmd: ", cmd)
        self.sock.connect(cmd)


    def subscribeTopic(self, topic):

        if self.topic == None:
            self.topic = topic
        else:    
            self.topic + topic

    
    def sendMessageToArduino(self, message, host, port):
        messageStr = messageSender_cffi.new("char *")
        host = messageSender_cffi.new("char *")
        messageStr[0] = message
        host[0] = host

        messageSender_c.sendMessageUDPForC(messageStr, host, port)

    '''
       Function run
    '''
    def run(self):
        print("Processor run on %s:%s" %(self.host, self.port))

        # mylist = []
        # smartplug = SmartDevice("SD001", "192.168.0.103:5600", \
        #                                                 "R0001", mylist)
        # smartlight = SmartDevice("SD002", "192.168.0.104:5600", \
        #                                                 "R0001", mylist)
        
        while True:
            '''[Access Database]
            [select data to table SmartDevice]
            '''
            


            topic = self.sock.recv(2, zmq.NOBLOCK)
            message = self.sock.recv(2, zmq.NOBLOCK)
            print("message ",message)
            msg_handler = message_handler.MessageHandler(topic, message)
            msg_handler.run()
 
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