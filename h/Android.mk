LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CPPFLAGS += -fexceptions

LOCAL_CPPFLAGS += -DCRYPTOPP_DISABLE_ASM -DCRYPTOPP_DISABLE_SSE2 -DCRYPTOPP_ENABLE_NAMESPACE_WEAK=1

LOCAL_MODULE    := cocos2dxh_static

LOCAL_MODULE_FILENAME := libcocos2dxh

LOCAL_SRC_FILES := bindingsJS/generatedauto/jsb_cocos2dxh_auto.cpp \
                   bindingsJS/HJSHelper.cpp \
                   cryptopp/3way.cpp \
                   cryptopp/adler32.cpp \
                   cryptopp/algebra.cpp \
                   cryptopp/algparam.cpp \
                   cryptopp/arc4.cpp \
                   cryptopp/asn.cpp \
                   cryptopp/authenc.cpp \
                   cryptopp/base32.cpp \
                   cryptopp/base64.cpp \
                   cryptopp/basecode.cpp \
                   cryptopp/bfinit.cpp \
                   cryptopp/blowfish.cpp \
                   cryptopp/blumshub.cpp \
                   cryptopp/camellia.cpp \
                   cryptopp/cast.cpp \
                   cryptopp/casts.cpp \
                   cryptopp/cbcmac.cpp \
                   cryptopp/ccm.cpp \
                   cryptopp/channels.cpp \
                   cryptopp/cmac.cpp \
                   cryptopp/cpu.cpp \
                   cryptopp/crc.cpp \
                   cryptopp/cryptlib_bds.cpp \
                   cryptopp/cryptlib.cpp \
                   cryptopp/default.cpp \
                   cryptopp/des.cpp \
                   cryptopp/dessp.cpp \
                   cryptopp/dh.cpp \
                   cryptopp/dh2.cpp \
                   cryptopp/dll.cpp \
                   cryptopp/dsa.cpp \
                   cryptopp/eax.cpp \
                   cryptopp/ec2n.cpp \
                   cryptopp/eccrypto.cpp \
                   cryptopp/ecp.cpp \
                   cryptopp/elgamal.cpp \
                   cryptopp/emsa2.cpp \
                   cryptopp/eprecomp.cpp \
                   cryptopp/esign.cpp \
                   cryptopp/files.cpp \
                   cryptopp/filters.cpp \
                   cryptopp/fips140.cpp \
                   cryptopp/fipsalgt.cpp \
                   cryptopp/gcm.cpp \
                   cryptopp/gf2_32.cpp \
                   cryptopp/gf2n.cpp \
                   cryptopp/gf256.cpp \
                   cryptopp/gfpcrypt.cpp \
                   cryptopp/gost.cpp \
                   cryptopp/gzip.cpp \
                   cryptopp/hex.cpp \
                   cryptopp/hmac.cpp \
                   cryptopp/hrtimer.cpp \
                   cryptopp/ida.cpp \
                   cryptopp/idea.cpp \
                   cryptopp/integer.cpp \
                   cryptopp/iterhash.cpp \
                   cryptopp/luc.cpp \
                   cryptopp/mars.cpp \
                   cryptopp/marss.cpp \
                   cryptopp/md2.cpp \
                   cryptopp/md4.cpp \
                   cryptopp/md5.cpp \
                   cryptopp/misc.cpp \
                   cryptopp/modes.cpp \
                   cryptopp/mqueue.cpp \
                   cryptopp/mqv.cpp \
                   cryptopp/nbtheory.cpp \
                   cryptopp/network.cpp \
                   cryptopp/oaep.cpp \
                   cryptopp/osrng.cpp \
                   cryptopp/panama.cpp \
                   cryptopp/pch.cpp \
                   cryptopp/pkcspad.cpp \
                   cryptopp/polynomi.cpp \
                   cryptopp/pssr.cpp \
                   cryptopp/pubkey.cpp \
                   cryptopp/queue.cpp \
                   cryptopp/rabin.cpp \
                   cryptopp/randpool.cpp \
                   cryptopp/rc2.cpp \
                   cryptopp/rc5.cpp \
                   cryptopp/rc6.cpp \
                   cryptopp/rdtables.cpp \
                   cryptopp/rijndael.cpp \
                   cryptopp/ripemd.cpp \
                   cryptopp/rng.cpp \
                   cryptopp/rsa.cpp \
                   cryptopp/rw.cpp \
                   cryptopp/safer.cpp \
                   cryptopp/salsa.cpp \
                   cryptopp/seal.cpp \
                   cryptopp/seed.cpp \
                   cryptopp/serpent.cpp \
                   cryptopp/sha.cpp \
                   cryptopp/sha3.cpp \
                   cryptopp/shacal2.cpp \
                   cryptopp/shark.cpp \
                   cryptopp/sharkbox.cpp \
                   cryptopp/simple.cpp \
                   cryptopp/skipjack.cpp \
                   cryptopp/socketft.cpp \
                   cryptopp/sosemanuk.cpp \
                   cryptopp/square.cpp \
                   cryptopp/squaretb.cpp \
                   cryptopp/strciphr.cpp \
                   cryptopp/tea.cpp \
                   cryptopp/tftables.cpp \
                   cryptopp/tiger.cpp \
                   cryptopp/tigertab.cpp \
                   cryptopp/trdlocal.cpp \
                   cryptopp/ttmac.cpp \
                   cryptopp/twofish.cpp \
                   cryptopp/vmac.cpp \
                   cryptopp/wait.cpp \
                   cryptopp/wake.cpp \
                   cryptopp/whrlpool.cpp \
                   cryptopp/winpipes.cpp \
                   cryptopp/xtr.cpp \
                   cryptopp/xtrcrypt.cpp \
                   cryptopp/zdeflate.cpp \
                   cryptopp/zinflate.cpp \
                   cryptopp/zlib_cryptopp.cpp \
                   helper/crypto/HCrypto.cpp \
                   helper/crypto/xxtea/xxtea.c \
                   helper/network/HAssetsManager.cpp \
                   helper/network/HHttpPacker.cpp \
                   helper/network/HHttpRequest.cpp \
                   helper/network/HHttpResponse.cpp \
                   helper/network/HSocket.cpp \
                   helper/network/bf/HBFPacket.cpp \
                   helper/network/bf/HBFPacketFactory.cpp \
                   helper/network/moshuo/HMSPacket.cpp \
                   helper/network/moshuo/HMSPacketFactory.cpp \
                   helper/store/HStore.cpp \
                   helper/store/HStorePaymentTransaction.cpp \
                   helper/store/HStoreProduct.cpp \
                   helper/tools/HAlgorithm.cpp \
                   helper/tools/HShaderCustom.cpp \
                   helper/tools/HStringConverter.cpp \
                   helper/ui/Action/HActionBlur.cpp \
                   helper/ui/Label/HLabelEmotion.cpp \
                   helper/ui/Scale9Sprite/HScale9Sprite.cpp \
                   helper/ui/Sprite/HSpriteBlur.cpp \
                   helper/ui/WebView/HWebView.cpp \
                   helper/ui/WebView/HWebViewImplAndroid.cpp \
                   msgpack/gcc_atomic.cpp \
                   msgpack/object.cpp \
                   msgpack/objectc.c \
                   msgpack/unpack.c \
                   msgpack/version.c \
                   msgpack/vrefbuffer.c \
                   msgpack/zone.c \
                   platform/android/CCNativeAndroid.cpp \
                   platform/android/CCNetworkAndroid.cpp \
                   platform/android/CCStorePaymentTransactionWrapper.cpp \
                   platform/android/HStoreImplAndroid.cpp \
                   platform/android/jni/Java_org_cocos2dxh_lib_Cocos2dxhHelper.cpp

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_jsb_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_iconv_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
                    
include $(BUILD_STATIC_LIBRARY)

$(call import-module,extensions)
$(call import-module,editor-support/cocosbuilder)
$(call import-module,editor-support/spine)
$(call import-module,editor-support/cocostudio)
$(call import-module,network)
$(call import-module,scripting/javascript/bindings)
$(call import-module,cocos2dxh/platform/third_party/android/prebuilt/libiconv)
