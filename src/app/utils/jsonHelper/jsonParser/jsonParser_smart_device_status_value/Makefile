#-----------------------------------------------------------------------------
#Makefile - src/app/utils/jsonParser/Makefile
# Copyright (c) Tien Nguyen Anh
# Modification history
# --------------------
#    Created: 2017-Jan-03 tien.nguyenanh94@gmail.com
#-----------------------------------------------------------------------------

ifneq ($(APP), unittest)
    override APP = jsonParser_smart_device_status_value
    TARGET = #none
    ARCHIVES = jsonParser_smart_device_status_value
endif

#-----------------------------------------------------------------------------
#source
SRCS = JsonParser_smart_device_status_value.cpp
OBJS = $(SRCS:.cpp=.o)
SUBOBJS = JsonCommon_smart_device_status_value.o

#-----------------------------------------------------------------------------
LIBDIRS_jsonCommon_smart_device_status_value  += $(LIDT_ROOT)/src/app/utils/jsonHelper/common/jsonCommon_smart_device_status_value
LIBRARY                                       += jsonCommon_smart_device_status_value

#-----------------------------------------------------------------------------
#include source code
INCS_DIRS += src/app/utils/jsonHelper/common/jsonCommon_smart_device_status_value \
			src/app/dataConverter \
			src/app/dataManager

#-----------------------------------------------------------------------------
CLEAN_DIRS += $(LIDT_ROOT)/src/app/utils/jsonHelper/common/jsonCommon_smart_device_status_value

#-----------------------------------------------------------------------------
#include makefile
include $(LIDT_MAKEDIR)/Makefile.app
