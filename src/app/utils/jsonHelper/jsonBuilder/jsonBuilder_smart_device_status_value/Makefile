#-----------------------------------------------------------------------------
#Makefile - src/app/utils/jsonHelper/Makefile
# Copyright (c) Trang Tran 2017
# Modification history
# --------------------
#    Created: 2017-Jan-05 tn-trang.tran@outlook.com
#-----------------------------------------------------------------------------

ifneq ($(APP), unittest)
    override APP = jsonBuilder_smart_device_status_value
    TARGET = #none
    ARCHIVES = jsonBuilder_smart_device_status_value
endif

#------------------------------------------------------------------------------
#source
SRCS = JsonBuilder_smart_device_status_value.cpp
OBJS = $(SRCS:.cpp=.o)
SUBOBJS = JsonCommon_smart_device_status_value.o
#-----------------------------------------------------------------------------
LIBDIRS_jsonCommon_smart_device_status_value  += $(LIDT_ROOT)/src/app/utils/jsonHelper/common/jsonCommon_smart_device_status_value
LIBRARY                                       += jsonCommon_smart_device_status_value

#------------------------------------------------------------------------------
#include source code
INCS_DIRS = src/app/utils/jsonHelper/common/jsonCommon_smart_device_status_value

#------------------------------------------------------------------------------
#include makefile
include $(LIDT_MAKEDIR)/Makefile.app
