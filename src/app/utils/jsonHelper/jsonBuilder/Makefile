#-----------------------------------------------------------------------------
#Makefile - src/app/utils/jsonHelper/Makefile
# Copyright (c) Trang Tran 2017
# Modification history
# --------------------
#    Created: 2017-Jan-05 tn-trang.tran@outlook.com
#-----------------------------------------------------------------------------

ifneq ($(APP), unittest)
    override APP = jsonBuilder
    TARGET = #none
    ARCHIVES = jsonBuilder
endif

#------------------------------------------------------------------------------
#source
SRCS = JsonBuilder.cpp
OBJS = $(SRCS:.cpp=.o)
SUBOBJS = JsonCommon.o
#-----------------------------------------------------------------------------
LIBDIRS_jsonCommon  += $(LIDT_ROOT)/src/app/utils/jsonHelper/common/
LIBRARY             += jsonCommon

#------------------------------------------------------------------------------
#include source code
INCS_DIRS = src/app/utils/jsonHelper/common

#------------------------------------------------------------------------------
#include makefile
include $(LIDT_MAKEDIR)/Makefile.app
