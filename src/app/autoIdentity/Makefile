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
    override APP = autoIdentity
    TARGET = #none
    ARCHIVES = autoIdentity
endif

#-----------------------------------------------------------------------------
#Source
SRCS = autoIdentity.cpp
OBJS = $(SRCS:.cpp=.o)

#-----------------------------------------------------------------------------
INCS_DIRS += src/app/dataManager 

#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
include $(LIDT_MAKEDIR)/Makefile.app 
