LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CPPFLAGS += -fexceptions

LOCAL_CPPFLAGS += -DCRYPTOPP_DISABLE_ASM -DCRYPTOPP_DISABLE_SSE2 -DCRYPTOPP_ENABLE_NAMESPACE_WEAK=1

LOCAL_MODULE    := cocos2dh_static

LOCAL_MODULE_FILENAME := libcocos2dh

LOCAL_SRC_FILES := \
assets-manager/HAssetsManager.cpp \
../js-bindings/bindings/auto/jsb_cocos2d_h_auto.cpp \
../js-bindings/bindings/manual/jsb_cocos2dh_manual.cpp

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_jsb_static
LOCAL_WHOLE_STATIC_LIBRARIES += jsb_chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += jsb_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += jsb_localstorage_static
LOCAL_WHOLE_STATIC_LIBRARIES += jsb_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += jsb_builder_static
LOCAL_WHOLE_STATIC_LIBRARIES += jsb_ui_static
LOCAL_WHOLE_STATIC_LIBRARIES += jsb_studio_static
LOCAL_WHOLE_STATIC_LIBRARIES += jsb_spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += msgpack_static
# LOCAL_WHOLE_STATIC_LIBRARIES += jsb_pluginx_static

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../cocos2d-js/frameworks/js-bindings/cocos2d-x/extensions

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
$(LOCAL_PATH)/../js-bindings/bindings/auto \
$(LOCAL_PATH)/../js-bindings/bindings/manual \
$(LOCAL_PATH)/../../cocos2d-js/frameworks/js-bindings/cocos2d-x/extensions \
                    
include $(BUILD_STATIC_LIBRARY)

$(call import-module,bindings)
$(call import-module,bindings/manual/chipmunk)
$(call import-module,bindings/manual/extension)
$(call import-module,bindings/manual/localstorage)
$(call import-module,bindings/manual/network)
$(call import-module,bindings/manual/cocosbuilder)
$(call import-module,bindings/manual/ui)
$(call import-module,bindings/manual/cocostudio)
$(call import-module,bindings/manual/spine)
$(call import-module,tools/build_msgpack)
# $(call import-module,cocos2d-x/plugin/jsbindings)
