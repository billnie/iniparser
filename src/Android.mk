LOCAL_PATH:= $(call my-dir)
################################################################################

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
		iniparser.c \
		dictionary.c
		
LOCAL_SHARED_LIBRARIES := \
		libutils \
		libcutils \
		liblog
#LOCAL_LDLIBS := -lpthread -ldl
LOCAL_MODULE:= libnini
LOCAL_MODULE_TAGS := eng 
include $(BUILD_STATIC_LIBRARY)
#include $(BUILD_SHARED_LIBRARY)
include $(CLEAR_VARS)
################################################################################