"""
File: processor.py
=========================

Copyright (c) Trang Tran 2017

Modified History
----------------
2017-Jan-08 Created tn-trang.tran@outlook.com
"""

import zmq

from cffi_interfaces.__cffi_jsonCommon import jsonCommon_c
from cffi_interfaces.__cffi_jsonCommon import jsonCommon_cffi

# ZeroMQ Context
context = zmq.Context()

# Define the socket using the "Context"
sock = context.socket(zmq.SUB)

# Define subscription and messages with prefix to accept.
sock.setsockopt_string(zmq.SUBSCRIBE, "SMART_PLUG_STATUS")
sock.connect("tcp://127.0.0.1:5563")

while True:
    message= sock.recv()
    print("Message: ", message)
    # topic, messagedata = message.split()
    # print("Topic: %s Message: %s" %(topic, message))
