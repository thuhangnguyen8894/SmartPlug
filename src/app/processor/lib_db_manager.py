"""
[description]
"""

from cffi_interfaces.__cffi_dbSmartDevice import db_mgr_cffi
from cffi_interfaces.__cffi_dbSmartDevice import db_mgr_c

import error_messages
import exceptions

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