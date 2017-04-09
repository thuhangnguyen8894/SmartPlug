import cffi
import os

#LIDT declare
LIDT_ROOT = os.getenv('LIDT_ROOT')
LIDT_LIBS = os.path.sep.join((LIDT_ROOT, 'obj', 'libs'))

DBSMARTDEVICE_FOR_C_INCLUDES = os.path.sep.join((LIDT_ROOT, 'src', 
                            'app', 'dbManager', 
                            'cWrapper'))
DATA_TYPE_DEF_INCLUDES = os.path.sep.join((LIDT_ROOT, 'src', 
                            'app', 'dataManager'))
DBSMARTDEVICE_FOR_C_LIBS = ["DBSmartDeviceForC"]

#define poco libraries
POCO_ROOT = os.getenv('POCO_ROOT')
POCO_INCLUDES = os.path.sep.join((POCO_ROOT, 'include'))
POCO_LIB_DIR = os.path.sep.join((POCO_ROOT, 'lib'))
POCO_LIBS = ["PocoFoundation", 'PocoFoundationd', "PocoData", 'PocoDatad', 'stdc++']
#POCO_LIBS = ["PocoNet", 'PocoNetd', 'stdc++']

#define mysql libraries
MYSQL_ROOT = os.getenv('MYSQL_CONN_ROOT')
MYSQL_CONN_INCLUDES = os.path.sep.join((MYSQL_ROOT, 'include'))
MYSQL_CONN_LIB_DIR = os.path.sep.join((MYSQL_ROOT, 'lib'))
MYSQL_CONN_LIBS = ["mysqlcppconn", 'stdc++']

db_mgr_cffi = cffi.FFI()
db_mgr_cffi.cdef("""
    typedef struct
    {
        char ip[20];
        long port;
    }Sender;

    typedef struct
    {
        char idTimer[10];
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
        char idTimer[10];
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
    

    bool insertToTableTimerForC(const SmartDeviceInfo* device);
    bool insertToTableDeviceTimerForC(const SmartDeviceInfo* device);
    bool selectIdTimerToTableTimerForC(SmartDeviceInfo* device);
""")

db_mgr_cffi = db_mgr_cffi.verify("""

                #include "DBSmartDeviceForC.h"
                #include "DataDef.h"

                """,
                include_dirs = [DBSMARTDEVICE_FOR_C_INCLUDES, DATA_TYPE_DEF_INCLUDES, 
                                POCO_INCLUDES, MYSQL_CONN_INCLUDES],
                libraries = DBSMARTDEVICE_FOR_C_LIBS + POCO_LIBS + MYSQL_CONN_LIBS,
                library_dirs = [LIDT_LIBS, POCO_LIB_DIR, MYSQL_CONN_LIB_DIR],
                modulename = "__cffi_DBSmartDevice")
