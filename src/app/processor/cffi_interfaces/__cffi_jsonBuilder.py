"""
File: __cffi_jsonBuilder.py
=========================

Copyright (c) Hang Nguyen 2017

Modified History
----------------
2017-Jan-05 Created thuhang.nguyen8894@gmail.com
"""

import cffi
import os

#LIDT declare
LIDT_ROOT = os.getenv('LIDT_ROOT')
LIDT_LIBS = os.path.sep.join((LIDT_ROOT, 'obj', 'libs'))

JSON_BUILDER_FOR_C_INCLUDES = os.path.sep.join((LIDT_ROOT, 'src', 
                            'app', 'utils', 'jsonHelper', 'cWrapper',
                            'jsonBuilderWrapper'))
JSON_BUILDER_FOR_C_LIBS = ["jsonBuilderForC"]

#define common libraries
BOOST_ROOT = os.getenv('BOOST_ROOT')
BOOST_INCLUDES = os.path.sep.join((BOOST_ROOT, 'include'))
BOOST_LIB_DIR = os.path.sep.join((BOOST_ROOT, 'lib'))
BOOST_LIBS = ["boost_serialization", 'boost_thread', 'stdc++']

jsonCommon_cffi = cffi.FFI()
jsonCommon_cffi.cdef("""
    bool buildJsonForC(const char* message, char** jsonString);
""")

jsonCommon_c = jsonCommon_cffi.verify("""

                #include "JsonBuilderForC.h"

                """,
                include_dirs = [JSON_BUILDER_FOR_C_INCLUDES, BOOST_INCLUDES],
                libraries = JSON_BUILDER_FOR_C_LIBS + BOOST_LIBS,
                library_dirs = [LIDT_LIBS, BOOST_LIB_DIR],
                modulename = "__cffi_jsonBuilder")
