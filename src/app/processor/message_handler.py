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
            traceback.print_exc()
            print("Error message 01: ", ex)
        except Exception as ex:
            import traceback
            traceback.print_exc()
            print("Error message 02: ", ex)

    def process_send_message_to_arduino(self):
        try:
            json_message = json.loads(self.message)
            id_device = json_message[constants.ATTR_DATA][constants.ATTR_ID_DEVICE]
            print('id_device ' + id_device)
            status_device = json_message[constants.ATTR_DATA][constants.ATTR_RELAY_STATUS_VALUE]
            print('status_device ' + status_device)
            self.lib_db_manager.message_sender(id_device, status_device)
        except exceptions.SendMessageToArduinoFailure as ex:
            import traceback
            traceback.print_exc()
            print("Error message 01: ", ex)
        except Exception as ex:
            import traceback
            traceback.print_exc()
            print("Error message 02: ", ex)

    def process_message(self):
        print("self.topic: ", self.topic)
        # print("ATTR_SMART_DEVICE_STATUS_VALUE: ", constants.ATTR_SMART_DEVICE_STATUS_VALUE)
        if self.topic == constants.ATTR_SMART_DEVICE_STATUS_VALUE:
            self.process_smart_device_status()
        elif self.topic == constants.ATTR_JSON_MOBILE_STATUS_VALUE:
            print('Send message Message Sender')
            self.process_send_message_to_arduino()

    def run(self):
        self.lib_db_manager = lib_db_manager.LibDBManager()
        self.process_message()
