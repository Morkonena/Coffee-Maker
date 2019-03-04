LOCAL_PATH := $(call my-dir)\..

include $(CLEAR_VARS)
LOCAL_MODULE := Cappuccino
LOCAL_SRC_FILES := $(LOCAL_PATH)\..\Cappuccino\libs\$(TARGET_ARCH_ABI)\libcappuccino.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := Box2D
LOCAL_SRC_FILES := $(LOCAL_PATH)\..\External\Box2D\obj\local\$(TARGET_ARCH_ABI)\libbox2d.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := mocha
LOCAL_SRC_FILES := $(wildcard Mocha/*.cpp)
LOCAL_CPPFLAGS := -DANDROID=1
LOCAL_C_INCLUDES := $(LOCAL_PATH)\..\Cappuccino\Cappuccino $(LOCAL_PATH)\..\External\Box2D
LOCAL_LDFLAGS := -Wl,--hash-style=both
LOCAL_LDLIBS := -landroid -llog
LOCAL_SHARED_LIBRARIES := Cappuccino
LOCAL_STATIC_LIBRARIES := Box2D
include $(BUILD_SHARED_LIBRARY)