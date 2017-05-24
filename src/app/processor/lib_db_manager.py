"""
[description]
"""

from cffi_interfaces.__cffi_dbSmartDevice import db_mgr_cffi
from cffi_interfaces.__cffi_dbSmartDevice import db_mgr_c

from cffi_interfaces.__cffi_messageSender import messageSender_cffi
from cffi_interfaces.__cffi_messageSender import messageSender_c

import error_messages
import exceptions

DBA_RESULT_OK = 1 

class LibDBManager(object):
    def __init__(self):
        pass

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

    def select_smartdevice(self):
        list_devices = []

        list_device_infos_ptr = db_mgr_cffi.new("SmartDeviceInfo**")
        number_elements = db_mgr_cffi.new("int*")

        result = db_mgr_c.selectDeviceToTableSmartDeviceForC(list_device_infos_ptr,
                                                            number_elements)

        if result != DBA_RESULT_OK:
            raise SelectTableSmartDeviceForCFailure(ERROR_SELECT_FROM_TABLE_SMART_DEVICE)

        for index in range(0, number_elements[0]):
            device_item = {}
            device_item['idSmartDevice'] = db_mgr_cffi.string(\
                        list_device_infos_ptr[0].device.idSmartDevice).decode('utf-8')
            device_item['idRoom'] =  db_mgr_cffi.string(\
                        list_device_infos_ptr[0].device.idRoom).decode('utf-8')
            device_item['nameSmartDevice'] =  db_mgr_cffi.string(\
                        list_device_infos_ptr[0].device.nameSmartDevice).decode('utf-8')
            
            list_devices.append(device_item)

        return list_devices
