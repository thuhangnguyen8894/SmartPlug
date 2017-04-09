import json
import constants

class JsonParser(object):
    def __init__(self):
        pass

    def parse_smart_devices_status(self, message):
        json_dict = json.loads(message)
        smart_device_info = {
            constants.ATTR_ID_SMART_DEVICE : json_dict[\
                                            constants.ATTR_DATA][\
                                            constants.ATTR_ID_SMART_DEVICE],
            constants.ATTR_ID_ROOM : json_dict[\
                                            constants.ATTR_DATA][\
                                            constants.ATTR_ID_ROOM],
            constants.ATTR_NAME_SMART_DEVICE : ""
        }

        device_timer_info = {
            constants.ATTR_ID_TIMER : json_dict[\
                                            constants.ATTR_TIMER][\
                                            constants.ATTR_ID_TIMER],
            constants.ATTR_ID_SMART_DEVICE : smart_device_info[\
                                            constants.ATTR_ID_SMART_DEVICE],
            constants.ATTR_STATE_ELECTRIC : json_dict[\
                                            constants.ATTR_DATA][\
                                            constants.ATTR_STATE_ELECTRIC],
            constants.ATTR_STATE_RELAY : json_dict[\
                                            constants.ATTR_DATA][\
                                            constants.ATTR_STATE_RELAY]
        }

        timer_info = {
            constants.ATTR_ID_TIMER : json_dict[\
                                            constants.ATTR_TIMER][\
                                            constants.ATTR_ID_TIMER],
            constants.ATTR_SEC_SD : json_dict[\
                                            constants.ATTR_TIMER][\
                                            constants.ATTR_SEC_SD],
            constants.ATTR_MIN_SD : json_dict[\
                                            constants.ATTR_TIMER][\
                                            constants.ATTR_MIN_SD],
            constants.ATTR_HOUR_SD : json_dict[\
                                            constants.ATTR_TIMER][\
                                            constants.ATTR_HOUR_SD],
            constants.ATTR_DAY_SD : json_dict[\
                                            constants.ATTR_TIMER][\
                                            constants.ATTR_DAY_SD],
            constants.ATTR_MONTH_SD : json_dict[\
                                            constants.ATTR_TIMER][\
                                            constants.ATTR_MONTH_SD],
            constants.ATTR_YEAR_SD : json_dict[\
                                            constants.ATTR_TIMER][\
                                            constants.ATTR_YEAR_SD],
        }

        sender_info = {
            constants.ATTR_IP : json_dict[\
                                        constants.ATTR_SENDER][\
                                        constants.ATTR_IP],
            constants.ATTR_PORT : json_dict[\
                                        constants.ATTR_SENDER][\
                                        constants.ATTR_PORT]
        }


        smart_device_status_info = {
            constants.ATTR_DEVICE_TIMER : device_timer_info,
            constants.ATTR_DEVICE : smart_device_info,
            constants.ATTR_SENDER : sender_info,
            constants.ATTR_TIMER : timer_info
        }