{
  'target_defaults': {
    'conditions': [
      ['OS == "win"', {
        'msvs_settings': {
          'VCCLCompilerTool': {
            'AdditionalOptions': [ '/TP' ],
          }
        },
        'defines': [
          '_WIN32',
          'WIN32',
          '_CRT_NONSTDC_NO_DEPRECATE',
          '_DEBUG',
          '_WINDOWS',
          '_USRDLL',
          '_WINDLL',
          '_UNICODE',
          'UNICODE'
        ],
        'link_settings': {
          'libraries': [
            '-ladvapi32.lib',
            '-liphlpapi.lib',
            '-lpsapi.lib',
            '-lshell32.lib',
            '-lws2_32.lib'
          ],
        },
      }],   # OS == "win"
      ['TO == "ios"', {
        'xcode_settings': {
          'TARGETED_DEVICE_FAMILY': '1,2',
          'CODE_SIGN_IDENTITY': 'iPhone Developer',
          'IPHONEOS_DEPLOYMENT_TARGET': '5.0',
          'ARCHS': '$(ARCHS_STANDARD_32_64_BIT)',
          # 'C_LANGUAGE_STANDARD': 'C99 [-std=c99]',
          'CLANG_CXX_LANGUAGE_STANDARD': 'c++11',
          'CLANG_CXX_LIBRARY': 'libc++',
        },
        'defines': [
          'CRYPTOPP_DISABLE_ASM',
          'CRYPTOPP_DISABLE_SSE2',
        ]
      }], # TO == "ios"
    ],    # conditions
  },

  'targets': [
    {
      'target_name': 'libcryptopp',
      'type': '<(library)',
      'include_dirs': [
        '../../external/cryptopp',
      ],
      'sources': [
        '../../external/cryptopp/3way.h',
        '../../external/cryptopp/adler32.h',
        '../../external/cryptopp/aes.h',
        '../../external/cryptopp/algebra.h',
        '../../external/cryptopp/algparam.h',
        '../../external/cryptopp/arc4.h',
        '../../external/cryptopp/argnames.h',
        '../../external/cryptopp/asn.h',
        '../../external/cryptopp/authenc.h',
        '../../external/cryptopp/base32.h',
        '../../external/cryptopp/base64.h',
        '../../external/cryptopp/basecode.h',
        '../../external/cryptopp/bench.h',
        '../../external/cryptopp/blowfish.h',
        '../../external/cryptopp/blumshub.h',
        '../../external/cryptopp/camellia.h',
        '../../external/cryptopp/cast.h',
        '../../external/cryptopp/cbcmac.h',
        '../../external/cryptopp/ccm.h',
        '../../external/cryptopp/channels.h',
        '../../external/cryptopp/cmac.h',
        '../../external/cryptopp/config.h',
        '../../external/cryptopp/cpu.h',
        '../../external/cryptopp/crc.h',
        '../../external/cryptopp/cryptlib.h',
        '../../external/cryptopp/default.h',
        '../../external/cryptopp/des.h',
        '../../external/cryptopp/dh.h',
        '../../external/cryptopp/dh2.h',
        '../../external/cryptopp/dll.h',
        '../../external/cryptopp/dmac.h',
        '../../external/cryptopp/dsa.h',
        '../../external/cryptopp/eax.h',
        '../../external/cryptopp/ec2n.h',
        '../../external/cryptopp/eccrypto.h',
        '../../external/cryptopp/ecp.h',
        '../../external/cryptopp/elgamal.h',
        '../../external/cryptopp/emsa2.h',
        '../../external/cryptopp/eprecomp.h',
        '../../external/cryptopp/esign.h',
        '../../external/cryptopp/factory.h',
        '../../external/cryptopp/files.h',
        '../../external/cryptopp/filters.h',
        '../../external/cryptopp/fips140.h',
        '../../external/cryptopp/fltrimpl.h',
        '../../external/cryptopp/gcm.h',
        '../../external/cryptopp/gf2_32.h',
        '../../external/cryptopp/gf2n.h',
        '../../external/cryptopp/gf256.h',
        '../../external/cryptopp/gfpcrypt.h',
        '../../external/cryptopp/gost.h',
        '../../external/cryptopp/gzip.h',
        '../../external/cryptopp/hex.h',
        '../../external/cryptopp/hmac.h',
        '../../external/cryptopp/hrtimer.h',
        '../../external/cryptopp/ida.h',
        '../../external/cryptopp/idea.h',
        '../../external/cryptopp/integer.h',
        '../../external/cryptopp/iterhash.h',
        '../../external/cryptopp/lubyrack.h',
        '../../external/cryptopp/luc.h',
        '../../external/cryptopp/mars.h',
        '../../external/cryptopp/md2.h',
        '../../external/cryptopp/md4.h',
        '../../external/cryptopp/md5.h',
        '../../external/cryptopp/mdc.h',
        '../../external/cryptopp/misc.h',
        '../../external/cryptopp/modarith.h',
        '../../external/cryptopp/modes.h',
        '../../external/cryptopp/modexppc.h',
        '../../external/cryptopp/mqueue.h',
        '../../external/cryptopp/mqv.h',
        '../../external/cryptopp/nbtheory.h',
        '../../external/cryptopp/network.h',
        '../../external/cryptopp/nr.h',
        '../../external/cryptopp/oaep.h',
        '../../external/cryptopp/oids.h',
        '../../external/cryptopp/osrng.h',
        '../../external/cryptopp/panama.h',
        '../../external/cryptopp/pch.h',
        '../../external/cryptopp/pkcspad.h',
        '../../external/cryptopp/polynomi.h',
        '../../external/cryptopp/pssr.h',
        '../../external/cryptopp/pubkey.h',
        '../../external/cryptopp/pwdbased.h',
        '../../external/cryptopp/queue.h',
        '../../external/cryptopp/rabin.h',
        '../../external/cryptopp/randpool.h',
        '../../external/cryptopp/rc2.h',
        '../../external/cryptopp/rc5.h',
        '../../external/cryptopp/rc6.h',
        '../../external/cryptopp/resource.h',
        '../../external/cryptopp/rijndael.h',
        '../../external/cryptopp/ripemd.h',
        '../../external/cryptopp/rng.h',
        '../../external/cryptopp/rsa.h',
        '../../external/cryptopp/rw.h',
        '../../external/cryptopp/safer.h',
        '../../external/cryptopp/salsa.h',
        '../../external/cryptopp/seal.h',
        '../../external/cryptopp/secblock.h',
        '../../external/cryptopp/seckey.h',
        '../../external/cryptopp/seed.h',
        '../../external/cryptopp/serpent.h',
        '../../external/cryptopp/serpentp.h',
        '../../external/cryptopp/sha.h',
        '../../external/cryptopp/sha3.h',
        '../../external/cryptopp/shacal2.h',
        '../../external/cryptopp/shark.h',
        '../../external/cryptopp/simple.h',
        '../../external/cryptopp/skipjack.h',
        '../../external/cryptopp/smartptr.h',
        '../../external/cryptopp/socketft.h',
        '../../external/cryptopp/sosemanuk.h',
        '../../external/cryptopp/square.h',
        '../../external/cryptopp/stdcpp.h',
        '../../external/cryptopp/strciphr.h',
        '../../external/cryptopp/tea.h',
        '../../external/cryptopp/tiger.h',
        '../../external/cryptopp/trdlocal.h',
        '../../external/cryptopp/trunhash.h',
        '../../external/cryptopp/ttmac.h',
        '../../external/cryptopp/twofish.h',
        '../../external/cryptopp/validate.h',
        '../../external/cryptopp/vmac.h',
        '../../external/cryptopp/wait.h',
        '../../external/cryptopp/wake.h',
        '../../external/cryptopp/whrlpool.h',
        '../../external/cryptopp/winpipes.h',
        '../../external/cryptopp/words.h',
        '../../external/cryptopp/xtr.h',
        '../../external/cryptopp/xtrcrypt.h',
        '../../external/cryptopp/zdeflate.h',
        '../../external/cryptopp/zinflate.h',
        '../../external/cryptopp/cryptopp_zlib.h',
        '../../external/cryptopp/3way.cpp',
        '../../external/cryptopp/adler32.cpp',
        '../../external/cryptopp/algebra.cpp',
        '../../external/cryptopp/algparam.cpp',
        '../../external/cryptopp/arc4.cpp',
        '../../external/cryptopp/asn.cpp',
        '../../external/cryptopp/authenc.cpp',
        '../../external/cryptopp/base32.cpp',
        '../../external/cryptopp/base64.cpp',
        '../../external/cryptopp/basecode.cpp',
        '../../external/cryptopp/bench.cpp',
        '../../external/cryptopp/bench2.cpp',
        '../../external/cryptopp/bfinit.cpp',
        '../../external/cryptopp/blowfish.cpp',
        '../../external/cryptopp/blumshub.cpp',
        '../../external/cryptopp/camellia.cpp',
        '../../external/cryptopp/cast.cpp',
        '../../external/cryptopp/casts.cpp',
        '../../external/cryptopp/cbcmac.cpp',
        '../../external/cryptopp/ccm.cpp',
        '../../external/cryptopp/channels.cpp',
        '../../external/cryptopp/cmac.cpp',
        '../../external/cryptopp/cpu.cpp',
        '../../external/cryptopp/crc.cpp',
        '../../external/cryptopp/cryptlib_bds.cpp',
        '../../external/cryptopp/cryptlib.cpp',
        '../../external/cryptopp/datatest.cpp',
        '../../external/cryptopp/default.cpp',
        '../../external/cryptopp/des.cpp',
        '../../external/cryptopp/dessp.cpp',
        '../../external/cryptopp/dh.cpp',
        '../../external/cryptopp/dh2.cpp',
        '../../external/cryptopp/dll.cpp',
        '../../external/cryptopp/dlltest.cpp',
        '../../external/cryptopp/dsa.cpp',
        '../../external/cryptopp/eax.cpp',
        '../../external/cryptopp/ec2n.cpp',
        '../../external/cryptopp/eccrypto.cpp',
        '../../external/cryptopp/ecp.cpp',
        '../../external/cryptopp/elgamal.cpp',
        '../../external/cryptopp/emsa2.cpp',
        '../../external/cryptopp/eprecomp.cpp',
        '../../external/cryptopp/esign.cpp',
        '../../external/cryptopp/files.cpp',
        '../../external/cryptopp/filters.cpp',
        '../../external/cryptopp/fips140.cpp',
        '../../external/cryptopp/fipsalgt.cpp',
        '../../external/cryptopp/fipstest.cpp',
        '../../external/cryptopp/gcm.cpp',
        '../../external/cryptopp/gf2_32.cpp',
        '../../external/cryptopp/gf2n.cpp',
        '../../external/cryptopp/gf256.cpp',
        '../../external/cryptopp/gfpcrypt.cpp',
        '../../external/cryptopp/gost.cpp',
        '../../external/cryptopp/gzip.cpp',
        '../../external/cryptopp/hex.cpp',
        '../../external/cryptopp/hmac.cpp',
        '../../external/cryptopp/hrtimer.cpp',
        '../../external/cryptopp/ida.cpp',
        '../../external/cryptopp/idea.cpp',
        '../../external/cryptopp/integer.cpp',
        '../../external/cryptopp/iterhash.cpp',
        '../../external/cryptopp/luc.cpp',
        '../../external/cryptopp/mars.cpp',
        '../../external/cryptopp/marss.cpp',
        '../../external/cryptopp/md2.cpp',
        '../../external/cryptopp/md4.cpp',
        '../../external/cryptopp/md5.cpp',
        '../../external/cryptopp/misc.cpp',
        '../../external/cryptopp/modes.cpp',
        '../../external/cryptopp/mqueue.cpp',
        '../../external/cryptopp/mqv.cpp',
        '../../external/cryptopp/nbtheory.cpp',
        '../../external/cryptopp/network.cpp',
        '../../external/cryptopp/oaep.cpp',
        '../../external/cryptopp/osrng.cpp',
        '../../external/cryptopp/panama.cpp',
        '../../external/cryptopp/pch.cpp',
        '../../external/cryptopp/pkcspad.cpp',
        '../../external/cryptopp/polynomi.cpp',
        '../../external/cryptopp/pssr.cpp',
        '../../external/cryptopp/pubkey.cpp',
        '../../external/cryptopp/queue.cpp',
        '../../external/cryptopp/rabin.cpp',
        '../../external/cryptopp/randpool.cpp',
        '../../external/cryptopp/rc2.cpp',
        '../../external/cryptopp/rc5.cpp',
        '../../external/cryptopp/rc6.cpp',
        '../../external/cryptopp/rdtables.cpp',
        '../../external/cryptopp/regtest.cpp',
        '../../external/cryptopp/rijndael.cpp',
        '../../external/cryptopp/ripemd.cpp',
        '../../external/cryptopp/rng.cpp',
        '../../external/cryptopp/rsa.cpp',
        '../../external/cryptopp/rw.cpp',
        '../../external/cryptopp/safer.cpp',
        '../../external/cryptopp/salsa.cpp',
        '../../external/cryptopp/seal.cpp',
        '../../external/cryptopp/seed.cpp',
        '../../external/cryptopp/serpent.cpp',
        '../../external/cryptopp/sha.cpp',
        '../../external/cryptopp/sha3.cpp',
        '../../external/cryptopp/shacal2.cpp',
        '../../external/cryptopp/shark.cpp',
        '../../external/cryptopp/sharkbox.cpp',
        '../../external/cryptopp/simple.cpp',
        '../../external/cryptopp/skipjack.cpp',
        '../../external/cryptopp/socketft.cpp',
        '../../external/cryptopp/sosemanuk.cpp',
        '../../external/cryptopp/square.cpp',
        '../../external/cryptopp/squaretb.cpp',
        '../../external/cryptopp/strciphr.cpp',
        '../../external/cryptopp/tea.cpp',
        '../../external/cryptopp/test.cpp',
        '../../external/cryptopp/tftables.cpp',
        '../../external/cryptopp/tiger.cpp',
        '../../external/cryptopp/tigertab.cpp',
        '../../external/cryptopp/trdlocal.cpp',
        '../../external/cryptopp/ttmac.cpp',
        '../../external/cryptopp/twofish.cpp',
        '../../external/cryptopp/validat1.cpp',
        '../../external/cryptopp/validat2.cpp',
        '../../external/cryptopp/validat3.cpp',
        '../../external/cryptopp/vmac.cpp',
        '../../external/cryptopp/wait.cpp',
        '../../external/cryptopp/wake.cpp',
        '../../external/cryptopp/whrlpool.cpp',
        '../../external/cryptopp/winpipes.cpp',
        '../../external/cryptopp/xtr.cpp',
        '../../external/cryptopp/xtrcrypt.cpp',
        '../../external/cryptopp/zdeflate.cpp',
        '../../external/cryptopp/zinflate.cpp',
        '../../external/cryptopp/cryptopp_zlib.cpp',
      ],
      'conditions': [
        ['OS != "win"', {
          'ldflags': [
            '-no-undefined',
            # '-export-symbols-regex \'^json_\'',
            '-version-info 0:5:8',
          ]
        }]    # OS != "win"
      ],    # conditions
    },
  ],    # targets

  'conditions': [
    ['TO == "ios"',
      {
        'xcode_settings': {
          'SDKROOT': 'iphoneos',
        }, # xcode_settings
      },
    ],  # TO == "ios"
  ],  # conditions
}