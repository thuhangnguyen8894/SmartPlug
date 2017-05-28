"""
[description]
"""

from cffi_interfaces.__cffi_dbSmartDevice import db_mgr_cffi
from cffi_interfaces.__cffi_dbSmartDevice import db_mgr_c

from cffi_interfaces.__cffi_messageSender import messageSender_cffi
from cffi_interfaces.__cffi_messageSender import messageSender_c

import error_messages
import exceptions

from ctypes import *

class LibDBManager(object):
    def __init__(self):
        pass

    def message_sender(self, id_device, status_device):
        print("Bao Khanh is here")
        if id_device == "SD001":
            print("id_device " + id_device)
            str1 = '192.168.0.106'
            host = messageSender_cffi.new("char[]", bytes(str1, "utf-8"))
            print(host[0])
        elif id_device == "SD002":
            print("id_device " + id_device)
            host = messageSender_cffi.new("char[]", bytes('192.168.0.103',"utf-8"))
            
        messageStr = messageSender_cffi.new("char[]", bytes(status_device, "utf-8"))
        print("status_devices: " + status_device)
        
        port = 5600

        messageSender_c.sendMessageUDPForC(messageStr, host, port)
        print("sendMessageUDPForC")
        

    def insert_time(self, smart_device_info_dict):
        timing_data_ptr = db_mgr_cffi.new("SmartDeviceInfo* ",\
                                          smart_device_info_dict)
        result_insert_table_timer = db_mgr_c.insertToTableTimerForC(\
                                                    timing_data_ptr)
        if not result_insert_table_timer:
            raise exceptions.InsertingTableTimerForCFailure(\
                                error_messages.ERROR_INSERT_INTO_TABLE_TIMER)

        result_insert_table_device_timer = db_mgr_c.insertToTableDeviceTimerForC(\
                                                                timing_data_ptr)
        if not result_insert_table_device_timer:
            raise exceptions.InsertingTableDeviceTimerForCFailure(\
                        error_messages.ERROR_INSERT_INTO_TABLE_DEVICE_TIMER) 