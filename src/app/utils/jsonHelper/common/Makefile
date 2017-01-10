#-----------------------------------------------------------------------------
#Makefile - src/app/utils/jsonHelper/common/Makefile
# Copyright (c) Trang Tran 2017
# Modification history
# --------------------
#    Created: 2017-Jan-05 tn-trang.tran@outlook.com
#-----------------------------------------------------------------------------

ifneq ($(APP), unittest)
    override APP = jsonCommon
    TARGET = #none
    ARCHIVES = jsonCommon
endif

#------------------------------------------------------------------------------
#source
SRCS = JsonCommon.cpp
OBJS = $(SRCS:.cpp=.o)

#------------------------------------------------------------------------------
#include source code
INCS_DIRS += src/app/dataManager/

#------------------------------------------------------------------------------
#include makefile
include $(LIDT_MAKEDIR)/Makefile.app
