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
            smart_device_info = self.json_parser.parse_smart_devices_status_info(\
                                                                self.message)
            print("smart_device_info:", smart_device_info)
            self.lib_db_manager.insert_time(smart_device_info)
        except exceptions.InsertingTableDeviceTimerForCFailure as ex:
            import traceback
            traceback.print_exc()
            print("Error message 01: ", ex)
        except Exception as ex:
            import traceback
            traceback.print_exc()
            print("Error message 02: ", ex)

    """[select data from table SmartDevice]
    [the 18th of May]
    """
    def process_select_table_smart_device(self):
        try:
            list_devices = self.lib_db_manager.select_smartdevice()
            emplements = len(list_devices)

            for x in range(emplements):
                print("Smart Device[", x, "]: ", 
                                 list_devices[x].device_item['idSmartDevice'])
                print(list_devices[x].device_item['idSmartDevice'])
                print(list_devices[x].device_item['nameSmartDevice'])
                print(list_devices[x].device_item['idRoom'])
        except exceptions.SelectTableSmartDeviceForCFailure as ex:
            import traceback
            traceback.print_exc()
            print("Error message 01: ", ex)
        except Exception as ex:
            import traceback
            traceback.print_exc()
            print("Error message 02: ", ex)

    def process_message(self):
        print("self.topic: ", self.topic)
        print("ATTR_SMART_DEVICE_STATUS_VALUE: ", constants.ATTR_SMART_DEVICE_STATUS_VALUE)

        """[select data from table SmartDevice]
        [the 18th of May]
        """
        if self.topic == "SELECTED_SMART_DEVICE":
            self.process_select_table_smart_device()


        if self.topic == constants.ATTR_SMART_DEVICE_STATUS_VALUE:
            self.process_smart_device_status()
        if self.topic == constants.ATTR_ANDROID_CONTROL_STATUS_DEVICE:
            self.process_android_control_status_device()

    def run(self):
        self.lib_db_manager = lib_db_manager.LibDBManager()
        self.process_message()
