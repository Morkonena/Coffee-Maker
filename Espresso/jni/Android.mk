LOCAL_PATH := $(call my-dir)\..

include $(CLEAR_VARS)
LOCAL_MODULE := Cappuccino
LOCAL_SRC_FILES := $(LOCAL_PATH)\..\Cappuccino\libs\$(TARGET_ARCH_ABI)\libcappuccino.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := Png
LOCAL_SRC_FILES := $(LOCAL_PATH)\..\External\Png\lib\$(TARGET_ARCH_ABI)\libpng.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := espresso
LOCAL_SRC_FILES := $(wildcard Espresso/*.cpp)
LOCAL_CPPFLAGS := -DANDROID=1
LOCAL_C_INCLUDES := $(LOCAL_PATH)\..\Cappuccino\Cappuccino $(LOCAL_PATH)\..\External\Png\include
LOCAL_LDFLAGS := -Wl,--hash-style=both
LOCAL_LDLIBS := -landroid -llog -lz
LOCAL_SHARED_LIBRARIES := Cappuccino
LOCAL_STATIC_LIBRARIES := Png
include $(BUILD_SHARED_LIBRARY)
