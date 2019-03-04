LOCAL_PATH := $(call my-dir)\..

include $(CLEAR_VARS)
LOCAL_MODULE := Cappuccino
LOCAL_SRC_FILES := $(LOCAL_PATH)\..\Cappuccino\libs\$(TARGET_ARCH_ABI)\libcappuccino.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := Fmod
LOCAL_SRC_FILES := $(LOCAL_PATH)\..\External\Fmod\libs\$(TARGET_ARCH_ABI)\libfmod.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := affogato
LOCAL_SRC_FILES := $(wildcard Affogato/*.cpp)
LOCAL_CPPFLAGS := -DANDROID=1
LOCAL_C_INCLUDES := $(LOCAL_PATH)\..\Cappuccino\Cappuccino $(LOCAL_PATH)\..\External\Fmod\include
LOCAL_LDFLAGS := -Wl,--hash-style=both
LOCAL_LDLIBS := -landroid -llog
LOCAL_SHARED_LIBRARIES := Cappuccino Fmod
include $(BUILD_SHARED_LIBRARY)