LOCAL_PATH := $(call my-dir)\..

include $(CLEAR_VARS)
LOCAL_MODULE := cm
LOCAL_SRC_FILES := $(LOCAL_PATH)\..\Cappuccino\libs\$(TARGET_ARCH_ABI)\libcappuccino.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cm2d
LOCAL_SRC_FILES := $(wildcard Affogato/*.cpp)
LOCAL_CPPFLAGS := -DANDROID=1
LOCAL_C_INCLUDES := $(LOCAL_PATH)\..\Cappuccino\Cappuccino
LOCAL_LDFLAGS := -Wl,--hash-style=both
LOCAL_LDLIBS := -landroid -llog
LOCAL_SHARED_LIBRARIES := Cappuccino
include $(BUILD_SHARED_LIBRARY)
