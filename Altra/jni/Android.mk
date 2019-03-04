LOCAL_PATH := $(call my-dir)\..

include $(CLEAR_VARS)
LOCAL_MODULE := Cappuccino
LOCAL_SRC_FILES := $(LOCAL_PATH)\..\Cappuccino\libs\$(TARGET_ARCH_ABI)\libcappuccino.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := Affogato
LOCAL_SRC_FILES := $(LOCAL_PATH)\..\Affogato\libs\$(TARGET_ARCH_ABI)\libaffogato.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := Espresso
LOCAL_SRC_FILES := $(LOCAL_PATH)\..\Espresso\libs\$(TARGET_ARCH_ABI)\libespresso.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := Mocha
LOCAL_SRC_FILES := $(LOCAL_PATH)\..\Mocha\libs\$(TARGET_ARCH_ABI)\libmocha.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := altra
LOCAL_SRC_FILES := $(wildcard Altra/*.cpp) $(wildcard Altra/Android/*.cpp) $(wildcard Altra/Simplex/*.cpp) 
LOCAL_CPPFLAGS := -DANDROID=1

LOCAL_C_INCLUDES := $(LOCAL_PATH)\..\Cappuccino\Cappuccino \
					$(LOCAL_PATH)\..\Affogato\Affogato \
					$(LOCAL_PATH)\..\Espresso\Espresso \
					$(LOCAL_PATH)\..\Mocha\Mocha

LOCAL_LDFLAGS := -Wl,--hash-style=both
LOCAL_LDLIBS := -landroid -llog
LOCAL_SHARED_LIBRARIES := Cappuccino Affogato Espresso Mocha
include $(BUILD_SHARED_LIBRARY)