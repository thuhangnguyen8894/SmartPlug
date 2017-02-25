"""
File: __cffi_jsonBuilder.py
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

JSON_BUILDER_SMART_DEVICE_STATUS_VALUE_FOR_C_INCLUDES = os.path.sep.join((LIDT_ROOT, 'src', 
                            'app', 'utils', 'jsonHelper', 'cWrapper',
                            'jsonBuilderWrapper', 'jsonBuilderWrapper_smart_device_status_value'))
JSON_BUILDERSMART_DEVICE_STATUS_VALUE_FOR_C_LIBS = ["jsonBuilder_smart_device_status_value_ForC"]

#define common libraries
BOOST_ROOT = os.getenv('BOOST_ROOT')
BOOST_INCLUDES = os.path.sep.join((BOOST_ROOT, 'include'))
BOOST_LIB_DIR = os.path.sep.join((BOOST_ROOT, 'lib'))
BOOST_LIBS = ["boost_serialization", 'boost_thread', 'stdc++']

jsonBuilder_smart_device_status_value_cffi = cffi.FFI()
jsonBuilder_smart_device_status_value_cffi.cdef("""
    bool buildJsonForC(const char* message, char** jsonString);
""")

jsonBuilder_smart_device_status_value_c = jsonBuilder_smart_device_status_value_cffi.verify("""

                #include "JsonBuilder_smart_device_status_value_ForC.h"

                """,
                include_dirs = [JSON_BUILDER_SMART_DEVICE_STATUS_VALUE_FOR_C_INCLUDES, BOOST_INCLUDES],
                libraries = JSON_BUILDERSMART_DEVICE_STATUS_VALUE_FOR_C_LIBS + BOOST_LIBS,
                library_dirs = [LIDT_LIBS, BOOST_LIB_DIR],
                modulename = "__cffi_jsonBuilder_smart_device_status_value")
