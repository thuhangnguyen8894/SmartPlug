"""
[description]
"""

from cffi_interfaces.__cffi_dbSmartDevice import db_mgr_cffi
from cffi_interfaces.__cffi_dbSmartDevice import db_mgr_c

from cffi_interfaces.__cffi_messageSender import messageSender_cffi
from cffi_interfaces.__cffi_messageSender import messageSender_c

import error_messages
import exceptions

class LibDBManager(object):
    def __init__(self):
        pass

    def message_sender(self, id_device, status_device):
        if id_device == "SD001":
            str1 = '192.168.0.106'
            host = messageSender_cffi.new("char[]", bytes(str1, "utf-8"))
            messageStr = self.fomart_messageStr(status_device)
        elif id_device == "SD002":
            host = messageSender_cffi.new("char[]", bytes('192.168.0.103',"utf-8"))
            messageStr = self.fomart_messageStr(status_device)
        
        port = 5600

        messageSender_c.sendMessageUDPForC(messageStr, host, port)
        print("sendMessageUDPForC")

    def fomart_messageStr(self, status_device):
        if status_device == "ACTIVE":
            messageStr = messageSender_cffi.new("char[]", bytes('1', "utf-8"))
        elif status_device == "UNACTIVE":
            messageStr = messageSender_cffi.new("char[]", bytes('0', "utf-8"))
        return messageStr

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