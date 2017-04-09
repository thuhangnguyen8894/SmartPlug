import threading
import json

import exceptions
import lib_db_manager
import constants

class MessageHandler(threading.Thread):
    def __init__(self, topic, message):
        threading.Thread.__init__(self)
        self.message = message
        self.topic = topic
    def parse_json(self):
        json_dict = json.loads(self.message)
        return json_dict
 
    def process_smart_devices_status(self):
        try:
            smart_device_info_dict = parse_json(self.message)
            self.lib_db_manager.insert_time(smart_device_info_dict)
        except exceptions.InsertingTableDeviceTimerForCFailure as ex:
            print("Error message: ", ex)
        except Exception as ex:
            print("Error message: ", ex)

    def process_message(self):
        if self.topic == constants.ATTR_SMART_DEVICE_STATUS_VALUE:
           self.process_smart_devices_status()
 
    def run(self):
        self.lib_db_manager = lib_db_manager.LibDBManager()
        self.process_message()
