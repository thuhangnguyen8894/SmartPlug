import json
import constants

class JsonParser(object):
    def __init__(self):
        pass

    def parse_smart_devices_status(self, message):
        json_dict = json.loads(message)
        print("json_dict:", json_dict)
        smart_device_info = {
            constants.ATTR_ID_SMART_DEVICE : bytes(json_dict[\
                                            constants.ATTR_DATA][\
                                            constants.ATTR_ID_SMART_DEVICE], "utf-8"),

            constants.ATTR_ID_ROOM : bytes(json_dict[\
                                            constants.ATTR_DATA][\
                                            constants.ATTR_ID_ROOM], "utf-8"),
            constants.ATTR_NAME_SMART_DEVICE : bytes(json_dict[\
                                            constants.ATTR_DATA][\
                                            constants.ATTR_NAME_SMART_DEVICE], "utf-8"),                             
        }
        # import pdb
        # pdb.set_trace()
        print(smart_device_info[constants.ATTR_ID_SMART_DEVICE])
        device_timer_info = {
            constants.ATTR_ID_TIMER : bytes(json_dict[\
                                            constants.ATTR_TIMER][\
                                            constants.ATTR_ID_TIMER], "utf-8"),
            constants.ATTR_ID_SMART_DEVICE : smart_device_info[\
                                            constants.ATTR_ID_SMART_DEVICE],
            constants.ATTR_STATE_ELECTRIC : bytes(json_dict[\
                                            constants.ATTR_DATA][\
                                            constants.ATTR_STATE_ELECTRIC], "utf-8"),
            constants.ATTR_STATE_RELAY : bytes(json_dict[\
                                            constants.ATTR_DATA][\
                                            constants.ATTR_STATE_RELAY], "utf-8")
        }

        timer_info = {
            constants.ATTR_ID_TIMER : bytes(json_dict[\
                                            constants.ATTR_TIMER][\
                                            constants.ATTR_ID_TIMER], "utf-8"),
            constants.ATTR_SEC_SD : int(json_dict[\
                                            constants.ATTR_TIMER][\
                                            constants.ATTR_SEC_SD]),
            constants.ATTR_MIN_SD : int(json_dict[\
                                            constants.ATTR_TIMER][\
                                            constants.ATTR_MIN_SD]),
            constants.ATTR_HOUR_SD : int(json_dict[\
                                            constants.ATTR_TIMER][\
                                            constants.ATTR_HOUR_SD]),
            constants.ATTR_DAY_SD : int(json_dict[\
                                            constants.ATTR_TIMER][\
                                            constants.ATTR_DAY_SD]),
            constants.ATTR_MONTH_SD : int(json_dict[\
                                            constants.ATTR_TIMER][\
                                            constants.ATTR_MONTH_SD]),
            constants.ATTR_YEAR_SD : int(json_dict[\
                                            constants.ATTR_TIMER][\
                                            constants.ATTR_YEAR_SD]),
        }

        sender_info = {
            constants.ATTR_IP : bytes(json_dict[\
                                        constants.ATTR_SENDER][\
                                        constants.ATTR_IP], "utf-8"),
            constants.ATTR_PORT : int(json_dict[\
                                        constants.ATTR_SENDER][\
                                        constants.ATTR_PORT])
        }


        smart_device_status_info = {
            constants.ATTR_DEVICE : smart_device_info,
            constants.ATTR_DEVICE_TIMER : device_timer_info,
            constants.ATTR_SENDER : sender_info,
            constants.ATTR_TIMER : timer_info
        }

        return smart_device_status_info