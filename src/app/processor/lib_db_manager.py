"""
[description]
"""

from cffi_interfaces.__cffi_dbSmartDevice import db_mgr_cffi
from cffi_interfaces.__cffi_dbSmartDevice import db_mgr_c

from cffi_interfaces.__cffi_messageSender import messageSender_cffi
from cffi_interfaces.__cffi_messageSender import messageSender_c

import error_messages
import exceptions
import constants

class LibDBManager(object):
    def __init__(self):
        pass

    def message_sender(self, id_device, status_device):
        if id_device == constants.ATTR_SD002_VALUE:
            host = messageSender_cffi.new("char[]", 
                               bytes(constants.ATTR_HOST_LIGHT_VALUE,"utf-8"))
            messageStr = self.fomart_messageStr(status_device)
            port = ATTR_PORT_LIGHT_VALUE
        elif id_device == constants.ATTR_SD001_VALUE:
            host = messageSender_cffi.new("char[]", 
                               bytes(constants.ATTR_HOST_PLUS_VALUE,"utf-8"))
            messageStr = self.fomart_messageStr(status_device)
            port = ATTR_PORT_PLUS_VALUE

        messageSender_c.sendMessageUDPForC(messageStr, host, port)

    def fomart_messageStr(self, status_device):
        status_device = int(status_device)
        if status_device == constants.ATTR_ACTIVE_VALUE:
            messageStr = messageSender_cffi.new("char[]", bytes('1', "utf-8"))
        elif status_device == constants.ATTR_UNACTIVE_VALUE:
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

        result_update_table_smartdevice = db_mgr_c.updateToTableSmartDeviceForC(\
                                                                timing_data_ptr)
        if not result_update_table_smartdevice:
            raise exceptions.UpdatingTableSmartDevice(\
                             error_messages.ERROR_UPDARE_TO_TABLE_SMARTDEVICE)