#-----------------------------------------------------------------------------
#Makefile - src/app/dbManager
# Modification history
# --------------------
#-----------------------------------------------------------------------------

ifneq ($(APP), unittest)
    override APP = dbManager
    TARGET = #none
    ARCHIVES = dbManager
endif

#------------------------------------------------------------------------------
#source
SRCS = DBSmartPlug.cpp
OBJS = $(SRCS:.cpp=.o)

#------------------------------------------------------------------------------
#include source code
INCS_DIRS += src/app/dataManager

#------------------------------------------------------------------------------
#include makefile
include $(LIDT_MAKEDIR)/Makefile.app

