#-----------------------------------------------------------------------------
#Makefile - src/app/utils/jsonHelper/common/Makefile
# Copyright (c) Trang Tran 2017
# Modification history
# --------------------
#    Created: 2017-Jan-05 tn-trang.tran@outlook.com
#-----------------------------------------------------------------------------

ifneq ($(APP), unittest)
    override APP = jsonCommon_smart_device_status_value
    TARGET = #none
    ARCHIVES = jsonCommon_smart_device_status_value
endif

#------------------------------------------------------------------------------
#source
SRCS = JsonCommon_smart_device_status_value.cpp
OBJS = $(SRCS:.cpp=.o)

#------------------------------------------------------------------------------
INCS_DIRS += src/app/dataManager
#------------------------------------------------------------------------------
#include makefile
include $(LIDT_MAKEDIR)/Makefile.app
