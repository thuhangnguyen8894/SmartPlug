import threading
import json

import exceptions
import lib_db_manager
import constants
import json_parser

class MessageHandler(threading.Thread):
    def __init__(self, topic, message):
        threading.Thread.__init__(self)
        self.message = message.decode('utf-8')
        self.topic = topic.decode('utf-8')
        self.json_parser = json_parser.JsonParser()

    def process_smart_device_status(self):
        try:
            smart_device_info = self.json_parser.parse_smart_devices_status(self.message)
            print("smart_device_info:", smart_device_info)
            self.lib_db_manager.insert_time(smart_device_info)
        except exceptions.InsertingTableDeviceTimerForCFailure as ex:
            import traceback
            traceback.print_exec()
            print("Error message: ", ex)
        except Exception as ex:
            print("Error message: ", ex)

    def process_message(self):
        print("self.topic: ", self.topic)
        print("ATTR_SMART_DEVICE_STATUS_VALUE: ", constants.ATTR_SMART_DEVICE_STATUS_VALUE)
        if self.topic == constants.ATTR_SMART_DEVICE_STATUS_VALUE:
            self.process_smart_device_status()

    def run(self):
        self.lib_db_manager = lib_db_manager.LibDBManager()
        self.process_message()
