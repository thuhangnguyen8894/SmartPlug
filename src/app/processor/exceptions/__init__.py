class InsertingTableDeviceTimerForCFailure(Exception):
    """
    This error occurs if insert_table_device_timer_for_c returns
    false.
    """
    pass

class InsertingTableTimerForCFailure(Exception):
    """[summary]   
    [description]
    """
    pass

class UpdatingTableSmartDevice(Exception):
    """[summary]   
    [description]
    """
    pass

class SendMessageToArduinoFailure(Exception):
    """[summary]
    [description]
    """
    pass

class ParseMessageFailure(Exception):
    """
    The error occurs when the message contains some invalid characters.
    """
    pass