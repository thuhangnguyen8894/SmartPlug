"""
[description]
"""

import cffi_interfaces.db_mgr_cffi as db_mgr_cffi
import cffi_interfaces.db_mgr_cffi as db_mgr_c

import error_messages
import exceptions

class LibDBManager(object):
    def __init__(self):
        pass

    def insert_time(self, smart_device_info_dict):
        timing_data_ptr = db_mgr_cffi.new("SmartDeviceInfo* ",\
                                          smart-device_info_dict)
        result = db_mgr_c.insert_to_table_Device_Timer_ForC(timing_data_ptr)
        if !result:
            raise exceptions.InsertingTableDeviceTimerForCFailure(\
                                 error_messages.ERROR_INSERT_INTO_TIME_TABLE) 

