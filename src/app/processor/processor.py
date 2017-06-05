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
import optionParser
import message_handler

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

    def run(self):
        print("Processor run on %s:%s" %(self.host, self.port))
        
        while True:
            message = self.sock.recv()
            print("message ",message)
            msg_handler = message_handler.MessageHandler(topic, message)
            msg_handler.run()
            time.sleep(1)
        self.sock.close()

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
