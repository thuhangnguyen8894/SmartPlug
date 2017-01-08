#-----------------------------------------------------------------------------
# Makefile - src/app/messenger
#
#
# Modified History
# ----------------
#-----------------------------------------------------------------------------

ifneq ($(APP), unittest)
    override APP = messenger
    TARGET = messenger
    PROGRAM = 
endif

#-----------------------------------------------------------------------------
SRCS = messenger.cpp
OBJS = $(SRCS:.cpp=.o)

#-----------------------------------------------------------------------------
USING_LANGUAGE = CPP

#-----------------------------------------------------------------------------
INCS_DIRS += src/app/messenger/messageReceiver

#-----------------------------------------------------------------------------
LIBDIRS_messageReceiver  = $(LIDT_ROOT)/src/app/messenger/messageReceiver
LIBRARY                  = messageReceiver

#-----------------------------------------------------------------------------
CLEAN_DIRS += $(LIDT_ROOT)/src/app/messenger/messageReceiver \
              $(LIDT_ROOT)/src/app/messenger/messageSender

#-----------------------------------------------------------------------------
include $(LIDT_MAKEDIR)/Makefile.app 
