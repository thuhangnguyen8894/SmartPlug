import cffi
import os

#LIDT declare
LIDT_ROOT = os.getenv('LIDT_ROOT')
LIDT_LIBS = os.path.sep.join((LIDT_ROOT, 'obj', 'libs'))

DBSMARTPLUG_FOR_C_INCLUDES = os.path.sep.join((LIDT_ROOT, 'src', 
                            'app', 'dbManager', 
                            'cWrapper_DBSmartPlug'))
DATA_TYPE_DEF_INCLUDES = os.path.sep.join((LIDT_ROOT, 'src', 
                            'app', 'dataManager'))
DBSMARTPLUG_FOR_C_LIBS = ["DBSmartPlugForC"]

#define poco libraries
POCO_ROOT = os.getenv('POCO_ROOT')
POCO_INCLUDES = os.path.sep.join((POCO_ROOT, 'include'))
POCO_LIB_DIR = os.path.sep.join((POCO_ROOT, 'lib'))
POCO_LIBS = ["PocoFoundation", 'PocoFoundationd', "PocoData", 'PocoDatad', 'stdc++']
#POCO_LIBS = ["PocoNet", 'PocoNetd', 'stdc++']

#define mysql libraries
MYSQL_ROOT = os.getenv('MYSQL_ROOT')
MYSQL_CONN_INCLUDES = os.path.sep.join((MYSQL_ROOT, 'include'))
MYSQL_CONN_LIB_DIR = os.path.sep.join((MYSQL_ROOT, 'lib'))
MYSQL_CONN_LIBS = ["mysqlcppconn", 'stdc++']

DBSmartPlug_cffi = cffi.FFI()
DBSmartPlug_cffi.cdef("""
    typedef struct
    {
        char ip[...];
        long port;
    }Sender;

    typedef struct
    {
        int secSP;
        int minSP;
        int hourSP;
        int daySP;
        int monthSP;
        int yearSP;
    }DatetimeSP;

    typedef struct 
    {
        char status_use_electric[5];
        char status_electric[10];
        char jack_relay[2];
        char ip_port_jack[20];
    }SmartDevice;

    typedef struct 
    {
        char id_timer[10];
    }IDAnything;

    typedef struct
    {
        SmartDevice data;
        Sender sender;
        IDAnything id;
        DatetimeSP datetimesp;
    }SmartDeviceInfo;


    bool update_to_db_ForC(const SmartDeviceInfo* smartplug);
""")

DBSmartPlug_c = DBSmartPlug_cffi.verify("""

                #include "DBSmartPlugForC.h"
                #include "DataDef.h"

                """,
                include_dirs = [DBSMARTPLUG_FOR_C_INCLUDES, DATA_TYPE_DEF_INCLUDES, 
                                POCO_INCLUDES, MYSQL_CONN_INCLUDES],
                libraries = DBSMARTPLUG_FOR_C_LIBS + POCO_LIBS + MYSQL_CONN_LIBS,
                library_dirs = [LIDT_LIBS, POCO_LIB_DIR, MYSQL_CONN_LIB_DIR],
                modulename = "__cffi_DBSmartPlug")