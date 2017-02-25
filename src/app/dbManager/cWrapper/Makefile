#-----------------------------------------------------------------------------
#Makefile - src/app/utils/jsonHelper/cWrapper/jsonBuilderWrapper
# Copyright (c) Tien Nguyen Anh
# Modification history
# --------------------
#    Created: 2017-Feb-16 tn-trang.tran@outlook.com
#-----------------------------------------------------------------------------

ifneq ($(APP), unittest)
    override APP = DBSmartDeviceForC
    TARGET = #none
    ARCHIVES = DBSmartDeviceForC
endif

#-----------------------------------------------------------------------------
#source
SRCS = DBSmartDeviceForC.cpp
OBJS = $(SRCS:.cpp=.o)

#-----------------------------------------------------------------------------
SUBOBJS = 	DBSmartDevice.o 

#-----------------------------------------------------------------------------
LIBDIRS_DBSmartDevice  += $(LIDT_ROOT)/src/app/dbManager/DBSmartDevice/
LIBRARY             += DBSmartDevice

#-----------------------------------------------------------------------------
#include source code
INCS_DIRS += /src/app/dbManager/DBSmartDevice \
             src/app/dataManager

#-----------------------------------------------------------------------------
CLEAN_DIRS += 	$(LIDT_ROOT)/src/app/dbManager/DBSmartDevice 

#-----------------------------------------------------------------------------
#include makefile
include $(LIDT_MAKEDIR)/Makefile.app