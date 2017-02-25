#-----------------------------------------------------------------------------
#Makefile - src/app/utils/jsonHelper/cWrapper/jsonBuilderWrapper
# Copyright (c) Tien Nguyen Anh
# Modification history
# --------------------
#    Created: 2016-Dec-21 tien.nguyenanh94@gmail.com
#-----------------------------------------------------------------------------

ifneq ($(APP), unittest)
    override APP = jsonBuilder_smart_device_status_value_ForC
    TARGET = #none
    ARCHIVES = jsonBuilder_smart_device_status_value_ForC
endif

#-----------------------------------------------------------------------------
#source
SRCS = JsonBuilder_smart_device_status_value_ForC.cpp
OBJS = $(SRCS:.cpp=.o)

#-----------------------------------------------------------------------------
SUBOBJS = 	JsonCommon_smart_device_status_value.o \
			JsonBuilder_smart_device_status_value.o

#-----------------------------------------------------------------------------
LIBDIRS_jsonCommon_smart_device_status_value  += $(LIDT_ROOT)/src/app/utils/jsonHelper/common/jsonCommon_smart_device_status_value
LIBRARY                                       += jsonCommon_smart_device_status_value
LIBDIRS_jsonBuilder_smart_device_status_value += $(LIDT_ROOT)/src/app/utils/jsonHelper/jsonBuilder/jsonBuilder_smart_device_status_value
LIBRARY                                       += jsonBuilder_smart_device_status_value

#-----------------------------------------------------------------------------
#include source code
INCS_DIRS += src/app/utils/jsonHelper/common/jsonCommon_smart_device_status_value \
			 src/app/utils/jsonHelper/jsonBuilder/jsonBuilder_smart_device_status_value \
			 src/app/dataManager

#-----------------------------------------------------------------------------
CLEAN_DIRS += 	$(LIDT_ROOT)/src/app/utils/jsonHelper/common/jsonCommon_smart_device_status_value \
				$(LIDT_ROOT)/src/app/utils/jsonHelper/jsonBuilder/jsonBuilder_smart_device_status_value

#-----------------------------------------------------------------------------
#include makefile
include $(LIDT_MAKEDIR)/Makefile.app