"""
File: __cffi_jsonCommon.py
=========================

Copyright (c) Tien Nguyen Anh

Modified History
----------------
2017-Jan-05 Created tien.nguyenanh94@gmail.com
2017-Jan-19 Modified thuhang.nguyen8894@gmail.com
"""

import cffi
import os

#LIDT declare
LIDT_ROOT = os.getenv('LIDT_ROOT')
LIDT_LIBS = os.path.sep.join((LIDT_ROOT, 'obj', 'libs'))

JSON_PARSER_FOR_C_INCLUDES = os.path.sep.join((LIDT_ROOT, 'src', 
                            'app', 'utils', 'jsonHelper', 'cWrapper',
                            'jsonParserWrapper'))
DATA_TYPE_DEF_INCLUDES = os.path.sep.join((LIDT_ROOT, 'src', 
                            'app', 'dataManager'))
JSON_PARSER_FOR_C_LIBS = ["jsonParserForC"]

#define common libraries
BOOST_ROOT = os.getenv('BOOST_ROOT')
BOOST_INCLUDES = os.path.sep.join((BOOST_ROOT, 'include'))
BOOST_LIB_DIR = os.path.sep.join((BOOST_ROOT, 'lib'))
BOOST_LIBS = ["boost_serialization", 'boost_thread', 'stdc++']

jsonParser_cffi = cffi.FFI()
jsonParser_cffi.cdef("""
    typedef struct
    {
        char ip[20];
        long port;
    }Sender;

    typedef struct
    {
        char idTimer[15];
        int secSD;
        int minSD;
        int hourSD;
        int daySD;
        int monthSD;
        int yearSD;
    }Timer;

    typedef struct 
    {
        char idSmartDevice[10];
        char idRoom[10];
        char nameSmartDevice [20];
    }SmartDevice;

    typedef struct
    {
        char idTimer[15];
        char idSmartDevice[10];
        char stateElectric[10];
        char stateRelay[10];
    }DeviceTimer;

    typedef struct
    {
        char idRoom[10];
        char nameRoom[20];
    }Room;

    typedef struct 
    {    
        char idUser[10];
        char nameUser[20];
        char password[20];
        char stateUser[10];
        char idUserStyle[10];
    }User;

    typedef struct
    {
        char idUserStyle[10];
        char nameUserStyle[20];
    }UserStyle;

    typedef struct
    {
        char idUserGuide[10];
        char nameUserGuide[20];
    }UserGuide;

    typedef struct
    {
        SmartDevice device;
        DeviceTimer deviceTimer;
        Sender sender;
        Timer timer;
    }SmartDeviceInfo;

    bool parseDataSmartDeviceJsonForC(const char* jsonString, SmartDeviceInfo* info);
""")

jsonParser_c = jsonParser_cffi.verify("""

                #include "JsonParserForC.h"

                """,
                include_dirs = [JSON_PARSER_FOR_C_INCLUDES,
                                DATA_TYPE_DEF_INCLUDES, BOOST_INCLUDES],
                libraries = JSON_PARSER_FOR_C_LIBS + BOOST_LIBS,
                library_dirs = [LIDT_LIBS, BOOST_LIB_DIR],
                modulename = "__cffi_jsonParser")