LOCAL_PATH := $(call my-dir)\..
include $(CLEAR_VARS)

LOCAL_MODULE := cappuccino
LOCAL_SRC_FILES := $(wildcard Cappuccino/*.cpp)
LOCAL_CPPFLAGS := -DANDROID=1
LOCAL_C_INCLUDES := $(LOCAL_PATH)\..\External\Glm
LOCAL_LDFLAGS := -Wl,--hash-style=both
LOCAL_LDLIBS := -landroid -llog -lGLESv3
include $(BUILD_SHARED_LIBRARY)