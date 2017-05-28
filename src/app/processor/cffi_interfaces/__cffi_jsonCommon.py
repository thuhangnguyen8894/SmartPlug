"""
File: __cffi_jsonCommon.py
=========================

Copyright (c) Tien Nguyen Anh

Modified History
----------------
2017-Jan-05 Created tien.nguyenanh94@gmail.com
"""

import cffi
import os

#LIDT declare
LIDT_ROOT = os.getenv('LIDT_ROOT')
LIDT_LIBS = os.path.sep.join((LIDT_ROOT, 'obj', 'libs'))

#include JsonCommon and DataDef
DATA_DEF_INCLUDES = os.path.sep.join((LIDT_ROOT, 'src', 'app', 'dataManager'))
JSONCOMMON_INCLUDES = os.path.sep.join((LIDT_ROOT, 'src', 'app', 'utils',
                                'jsonHelper', 'common'))
JSON_COMMON_FOR_C_INCLUDES = os.path.sep.join((LIDT_ROOT, 'src', 'app',
                                'utils', 'jsonHelper', 'cWrapper',
                                'jsonCommonWrapper'))

JSON_COMMON_LIBS = ["jsonCommonForC"]

#define common libraries
BOOST_ROOT = os.getenv('BOOST_ROOT')
BOOST_INCLUDES = os.path.sep.join((BOOST_ROOT, 'include'))
BOOST_LIB_DIR = os.path.sep.join((BOOST_ROOT, 'lib'))
BOOST_LIBS = ["boost_serialization", 'boost_thread', 'stdc++']

jsonCommon_cffi = cffi.FFI()
jsonCommon_cffi.cdef("""

   #define MAX_SMART_DEVICE_STATUS_VALUE 120
   #define JSON_TOKEN_SIZE 3
   #define JSON_DATA_SIZE 5
   #define SENDER_TOKEN_SIZE 2
   #define DATE_TIME_TOKEN_SIZE 3
   #define STATUS_TOKEN_SIZE 2

   #define COLON_SPLITTER ...
   #define SEMICOLON_SPLITTER ...
   #define DOT_SPLITTER ...
   #define SLASH_SPLITTER ...
   #define UNDERSCORS_SPLITTER ...

   #define ATTR_JSON_MESSAGE_TYPE ...
   #define ATTR_JSON_MESSAGE_TYPE_VALUE ...
   #define ATTR_JSON_MOBILE_STATUS_VALUE ...

   #define ATTR_JSON_ID_DEVICE ...
   #define ATTR_JSON_NAME_DEVICE ...

   #define ATTR_JSON_RELAY_STATUS_VALUE ...
   #define ATTR_JSON_RELAY_STATUS_VALUE_ACTIVE ...
   #define ATTR_JSON_RELAY_STATUS_VALUE_UNACTIVE ...

   #define ATTR_JSON_ELECTRIC_STATUS_VALUE ...
   #define ATTR_JSON_ELECTRIC_MESSAGE_VALUE_ON ...
   #define ATTR_JSON_ELECTRIC_MESSAGE_VALUE_OFF ...

   #define ATTR_JSON_ID_ROOM_VALUE ...
   #define ATTR_JSON_ID_TIMER_VALUE ...

   #define MESSAGE_TYPE_DEFAULT_VALUE ...
   #define MESSAGE_TYPE_SMART_DEVICE_STATUS_VALUE ...
   #define MESSAGE_TYPE_MOBILE_STATUS_VALUE ...

   #define ATTR_JSON_DATA ...

   #define ATTR_JSON_TIMER ...
   #define ATTR_JSON_YEAR ...
   #define ATTR_JSON_MONTH ...
   #define ATTR_JSON_DAY ...
   #define ATTR_JSON_HOUR ...
   #define ATTR_JSON_MINUTES ...
   #define ATTR_JSON_SECOND ...

   #define ATTR_JSON_SENDER ...
   #define ATTR_JSON_IP ...
   #define ATTR_JSON_PORT ...

   typedef enum
   {
       MESSAGE_TYPE_DEFAULT = -1,
       MESSAGE_TYPE_SMART_DEVICE_STATUS,
       MESSAGE_TYPE_MOBILE_STATUS
   }MESSAGE_TYPE;

       void getJSONMessageTypeForC(const char* message, MESSAGE_TYPE* messageType);
       bool convertMessageTypeToStrForC(const MESSAGE_TYPE* messageType, char** messageTypeStr);
       bool isSensorMessageForC(const char* message);
""")

jsonCommon_c = jsonCommon_cffi.verify("""
                #include "DataDef.h"
                #include "JsonCommonForC.h"
                """,
                include_dirs = [JSON_COMMON_FOR_C_INCLUDES,
                                DATA_DEF_INCLUDES, BOOST_INCLUDES],
                libraries = JSON_COMMON_LIBS + BOOST_LIBS,
                library_dirs = [LIDT_LIBS, BOOST_LIB_DIR],
                modulename = "__cffi_jsonCommon")