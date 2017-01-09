#-----------------------------------------------------------------------------
#Makefile - src/app/dataConverter
# Copyright (c) Hang Nguyen 2016
# Modification history
# --------------------
#    Created: 2016-Dec-04 thuhang.nguyen8894@gmail.com
#-----------------------------------------------------------------------------

ifneq ($(APP), unittest)
	override APP = dataConverter
	TARGET = #none
	ARCHIVES = dataConverter
endif

#------------------------------------------------------------------------------
#source
SRCS = smartplug.cpp
OBJS = $(SRCS:.cpp=.o)

#------------------------------------------------------------------------------
#include source code
INCS = .

#------------------------------------------------------------------------------
#include makefile
include $(LIDT_MAKEDIR)/Makefile.app
