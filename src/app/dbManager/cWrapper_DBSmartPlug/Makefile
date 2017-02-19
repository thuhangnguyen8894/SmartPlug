#-----------------------------------------------------------------------------
#Makefile - src/app/utils/jsonHelper/cWrapper/jsonBuilderWrapper
# Copyright (c) Tien Nguyen Anh
# Modification history
# --------------------
#    Created: 2017-Feb-16 tn-trang.tran@outlook.com
#-----------------------------------------------------------------------------

ifneq ($(APP), unittest)
    override APP = DBSmartPlugForC
    TARGET = #none
    ARCHIVES = DBSmartPlugForC
endif

#-----------------------------------------------------------------------------
#source
SRCS = DBSmartPlugForC.cpp
OBJS = $(SRCS:.cpp=.o)

#-----------------------------------------------------------------------------
SUBOBJS = 	DBSmartPlug.o 

#-----------------------------------------------------------------------------
LIBDIRS_DBSmartPlug  += $(LIDT_ROOT)/src/app/dbManager/DBSmartPlug/
LIBRARY             += DBSmartPlug

#-----------------------------------------------------------------------------
#include source code
INCS_DIRS += /src/app/dbManager/DBSmartPlug \
             src/app/dataManager

#-----------------------------------------------------------------------------
CLEAN_DIRS += 	$(LIDT_ROOT)/src/app/dbManager/DBSmartPlug 

#-----------------------------------------------------------------------------
#include makefile
include $(LIDT_MAKEDIR)/Makefile.app