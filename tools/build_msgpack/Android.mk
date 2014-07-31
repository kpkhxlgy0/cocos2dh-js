LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := msgpack_static

LOCAL_MODULE_FILENAME := libmsgpack

LOCAL_SRC_FILES := \
../../../cocos2dh-js/external/msgpack-c/src/objectc.c \
../../../cocos2dh-js/external/msgpack-c/src/unpack.c \
../../../cocos2dh-js/external/msgpack-c/src/version.c \
../../../cocos2dh-js/external/msgpack-c/src/vrefbuffer.c \
../../../cocos2dh-js/external/msgpack-c/src/zone.c \
../../../cocos2dh-js/external/msgpack-c/src/object.cpp

LOCAL_CXXFLAGS += -fexceptions

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../cocos2dh-js/external/msgpack-c/src

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../../cocos2dh-js/external/msgpack-c/src
                    
include $(BUILD_STATIC_LIBRARY)
