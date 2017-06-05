import threading
import json

import exceptions
import lib_db_manager
import constants
import json_parser
import error_messages

class MessageHandler(threading.Thread):
    def __init__(self, topic, message):
        threading.Thread.__init__(self)
        self.message = message.decode('utf-8')
        print("Message: aaaa%saaaaa" % self.message)
        self.topic = self.get_message_topic(self.message)
        self.json_parser = json_parser.JsonParser()

    def get_message_topic(self, message):
        message_topic = None
        try:
            json_message = json.loads(message)
            message_topic = json_message[constants.ATTR_MESSAGE_TYPE]
        except json.decoder.JSONDecodeError:
            print("Error message: ",\
                            error_messages.ERROR_PARSE_TOPIC_MESSAGE_FAILURE)

        return message_topic

    def process_smart_device_status(self):
        try:
            smart_device_info = self.json_parser.parse_smart_devices_status(self.message)
            self.lib_db_manager.insert_time(smart_device_info)
        except exceptions.InsertingTableDeviceTimerForCFailure as ex:
            import traceback
            traceback.print_exc()
            print("Error message: ", ex)
        except exceptions.ParseMessageFailure as ex:
            print("Error message: ", ex)
        except Exception as ex:
            import traceback
            traceback.print_exc()
            print("Error message 02: ", ex)

    def process_send_message_to_arduino(self):
        try:
            json_message = json.loads(self.message)
            id_device = json_message[constants.ATTR_DATA][constants.ATTR_ID_DEVICE]
            status_device = json_message[constants.ATTR_DATA][constants.ATTR_RELAY_STATUS_VALUE]
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
        if self.topic == constants.ATTR_SMART_DEVICE_STATUS_VALUE:
            self.process_smart_device_status()
        elif self.topic == constants.ATTR_JSON_MOBILE_STATUS_VALUE:
            self.process_send_message_to_arduino()

    def run(self):
        self.lib_db_manager = lib_db_manager.LibDBManager()
        self.process_message()
