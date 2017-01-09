#-----------------------------------------------------------------------------
#Makefile - src/app/utils/jsonParser/Makefile
# Copyright (c) Tien Nguyen Anh
# Modification history
# --------------------
#    Created: 2017-Jan-03 tien.nguyenanh94@gmail.com
#-----------------------------------------------------------------------------

ifneq ($(APP), unittest)
    override APP = jsonParser
    TARGET = #none
    ARCHIVES = jsonParser
endif

#-----------------------------------------------------------------------------
#source
SRCS = JsonParser.cpp
OBJS = $(SRCS:.cpp=.o)
SUBOBJS = JsonCommon.o

#-----------------------------------------------------------------------------
LIBDIRS_jsonCommon  += $(LIDT_ROOT)/src/app/utils/jsonHelper/common/
LIBRARY             += jsonCommon

#-----------------------------------------------------------------------------
#include source code
INCS_DIRS += src/app/utils/jsonHelper/common \
			src/app/dataConverter \
			src/app/dataManager

#-----------------------------------------------------------------------------
CLEAN_DIRS += $(LIDT_ROOT)/src/app/utils/jsonHelper/common

#-----------------------------------------------------------------------------
#include makefile
include $(LIDT_MAKEDIR)/Makefile.app
