#-----------------------------------------------------------------------------
# Makefile - src/app/processor/cffi_interfaces
#
# Copyright (c) Tien Nguyen Anh
#
# Modified History
# ----------------
# 2017-Jan-05 Created tien.nguyenanh94@gmail.com 
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
#cffi targets
CFFI_SRCS = __cffi_jsonCommon_smart_device_status_value.py \
			__cffi_jsonBuilder_smart_device_status_value.py \
			__cffi_jsonParser_smart_device_status_value.py \
			__cffi_messageSender.py \
			__cffi_DBSmartDevice.py

CFFI_OBJS = $(CFFI_SRCS:.py=.pyc)

#-----------------------------------------------------------------------------
LIBDIRS_jsonCommon_smart_device_status_value_ForC  += $(LIDT_ROOT)/src/app/utils/jsonHelper/cWrapper/jsonCommonWrapper/jsonCommonWrapper_smart_device_status_value
LIBRARY                                            += jsonCommon_smart_device_status_value_ForC
LIBDIRS_jsonParser_smart_device_status_value_ForC  += $(LIDT_ROOT)/src/app/utils/jsonHelper/cWrapper/jsonParserWrapper/jsonParserWrapper_smart_device_status_value
LIBRARY                                            += jsonParser_smart_device_status_value_ForC
LIBDIRS_jsonBuilder_smart_device_status_value_ForC += $(LIDT_ROOT)/src/app/utils/jsonHelper/cWrapper/jsonBuilderWrapper/jsonBuilderWrapper_smart_device_status_value
LIBRARY                                            += jsonBuilder_smart_device_status_value_ForC
LIBDIRS_messageSenderForC   += $(LIDT_ROOT)/src/app/messenger/messageSender/cWrapper
LIBRARY                     += messageSenderForC
LIBDIRS_DBSmartDeviceForC   += $(LIDT_ROOT)/src/app/dbManager/cWrapper
LIBRARY                     += DBSmartDeviceForC

#-----------------------------------------------------------------------------
CLEAN_DIRS += $(LIDT_ROOT)/src/app/messenger/messageSender/cWrapper
CLEAN_DIRS += $(LIDT_ROOT)/src/app/utils/jsonHelper/cWrapper/jsonCommonWrapper/jsonCommonWrapper_smart_device_status_value
CLEAN_DIRS += $(LIDT_ROOT)//src/app/utils/jsonHelper/cWrapper/jsonParserWrapper/jsonParserWrapper_smart_device_status_value
CLEAN_DIRS += $(LIDT_ROOT)/src/app/utils/jsonHelper/cWrapper/jsonBuilderWrapper/jsonBuilderWrapper_smart_device_status_value
CLEAN_DIRS += $(LIDT_ROOT)/src/app/dbManager/cWrapper
#-----------------------------------------------------------------------------
include $(LIDT_MAKEDIR)/Makefile.app 