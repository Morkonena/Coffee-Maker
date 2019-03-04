LOCAL_PATH := $(call my-dir)\..
include $(CLEAR_VARS)

LOCAL_MODULE := box2d
LOCAL_SRC_FILES := $(wildcard Box2D/Collision/*.cpp) \
				   $(wildcard Box2D/Collision/Shapes/*.cpp) \
				   $(wildcard Box2D/Common/*.cpp) \
				   $(wildcard Box2D/Dynamics/*.cpp) \
				   $(wildcard Box2D/Dynamics/Contacts/*.cpp) \
				   $(wildcard Box2D/Dynamics/Joints/*.cpp) \
				   $(wildcard Box2D/Rope/*.cpp)
				   
include $(BUILD_STATIC_LIBRARY)