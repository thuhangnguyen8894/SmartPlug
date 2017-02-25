#-----------------------------------------------------------------------------
# Makefile - src/app/messenger/messageReceiver
#
# Copyright (c) Tien Nguyen Anh
#
# Modified History
# ----------------
# 2016-Dec-08 Created Tien Nguyen Anh 
#-----------------------------------------------------------------------------

ifneq ($(APP), unittest)
    override APP = messageReceiver
    TARGET = #none
    ARCHIVES = messageReceiver
endif

#-----------------------------------------------------------------------------
#Source
SRCS = MessageReceiver.cpp
OBJS = $(SRCS:.cpp=.o)
SUBOBJS += JsonBuilder_smart_device_status_value.o
SUBOBJS += JsonCommon_smart_device_status_value.o
SUBOBJS += timer.o
SUBOBJS += autoIdentity.o

#------------------------------------------------------------------------------
#include source code
INCS_DIRS = src/app/utils/jsonHelper/common/jsonCommon_smart_device_status_value \
			src/app/utils/jsonHelper/jsonBuilder/jsonBuilder_smart_device_status_value \
			src/app/timer \
			src/app/autoIdentity \
			src/app/dataManager
#-----------------------------------------------------------------------------
LIBDIRS_jsonCommon_smart_device_status_value  = $(LIDT_ROOT)/src/app/utils/jsonHelper/common/jsonCommon_smart_device_status_value/
LIBRARY                                      += jsonCommon_smart_device_status_value
LIBDIRS_jsonBuilder_smart_device_status_value = $(LIDT_ROOT)/src/app/utils/jsonHelper/jsonBuilder/jsonBuilder_smart_device_status_value/
LIBRARY                                      += jsonBuilder_smart_device_status_value

#-----------------------------------------------------------------------------
CLEAN_DIRS += $(LIDT_ROOT)/src/app/utils/jsonHelper/common/jsonCommon_smart_device_status_value \
              $(LIDT_ROOT)/src/app/utils/jsonHelper/jsonBuilder/jsonBuilder_smart_device_status_value

#-----------------------------------------------------------------------------
include $(LIDT_MAKEDIR)/Makefile.app 
