LOCAL_PATH:= $(call my-dir)


########################
# include $(CLEAR_VARS)
# LOCAL_MODULE := libnini
# LOCAL_SRC_FILES := libnini/libnini.a
# LOCAL_MODULE_TAGS := eng
# LOCAL_MODULE_SUFFIX := .a
# LOCAL_MODULE_CLASS := STATIC_LIBRARIES
# include $(BUILD_PREBUILT)
########################

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
		iniexample.c
		

LOCAL_SHARED_LIBRARIES := \
	libcutils  liblog libutils  libz \


LOCAL_C_INCLUDES:= \
	$(LOCAL_PATH)/../src


LOCAL_STATIC_LIBRARIES += libnini	

LOCAL_CFLAGS += -Wno-multichar 
#CFLAGS += -Wno-error=date-time
LOCAL_CFLAGS += -Wno-error=date-time
EXTRA_CFLAGS += -Wno-date-time
LOCAL_CFLAGS += -Wno-multichar -Werror -Wall 
LOCAL_CFLAGS += -Wno-unused-variable
LOCAL_CFLAGS += -Wno-unused-parameter
LOCAL_CFLAGS += -Wno-sign-compare
LOCAL_CFLAGS += -Wno-unused-function
LOCAL_CFLAGS += -Wno-pointer-sign
LOCAL_CFLAGS += -Wno-format
LOCAL_CFLAGS += -Wno-error=writable-strings
LOCAL_CFLAGS:+= -Wimplicit-function-declaration

LOCAL_MODULE_TAGS := eng

LOCAL_MODULE:= iniexam

include $(BUILD_EXECUTABLE)