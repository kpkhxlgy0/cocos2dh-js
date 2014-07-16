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
      }], # TO == "ios"
    ],    # conditions
  },

  'targets': [
    {
      'target_name': 'libmsgpack',
      'type': '<(library)',
      'include_dirs': [
        '../../external/msgpack-c/src',
      ],
      'sources': [
        '../../external/msgpack-c/src/gcc_atomic.h',
        '../../external/msgpack-c/src/msgpack.h',
        '../../external/msgpack-c/src/objectc.c',
        '../../external/msgpack-c/src/unpack.c',
        '../../external/msgpack-c/src/version.c',
        '../../external/msgpack-c/src/vrefbuffer.c',
        '../../external/msgpack-c/src/zone.c',
        '../../external/msgpack-c/src/msgpack.hpp',
        '../../external/msgpack-c/src/gcc_atomic.cpp',
        '../../external/msgpack-c/src/object.cpp',
        '../../external/msgpack-c/src/msgpack/object.h',
        '../../external/msgpack-c/src/msgpack/object.hpp',
        '../../external/msgpack-c/src/msgpack/pack_define.h',
        '../../external/msgpack-c/src/msgpack/pack_template.h',
        '../../external/msgpack-c/src/msgpack/pack.h',
        '../../external/msgpack-c/src/msgpack/pack.hpp',
        '../../external/msgpack-c/src/msgpack/sbuffer.h',
        '../../external/msgpack-c/src/msgpack/sbuffer.hpp',
        '../../external/msgpack-c/src/msgpack/sysdep.h',
        '../../external/msgpack-c/src/msgpack/type.hpp',
        '../../external/msgpack-c/src/msgpack/unpack_define.h',
        '../../external/msgpack-c/src/msgpack/unpack_template.h',
        '../../external/msgpack-c/src/msgpack/unpack.h',
        '../../external/msgpack-c/src/msgpack/unpack.hpp',
        '../../external/msgpack-c/src/msgpack/version.h',
        '../../external/msgpack-c/src/msgpack/vrefbuffer.h',
        '../../external/msgpack-c/src/msgpack/vrefbuffer.hpp',
        '../../external/msgpack-c/src/msgpack/zbuffer.h',
        '../../external/msgpack-c/src/msgpack/zbuffer.hpp',
        '../../external/msgpack-c/src/msgpack/zone.h',
        '../../external/msgpack-c/src/msgpack/zone.hpp',
        '../../external/msgpack-c/src/msgpack/type/bool.hpp',
        '../../external/msgpack-c/src/msgpack/type/define.hpp',
        '../../external/msgpack-c/src/msgpack/type/deque.hpp',
        '../../external/msgpack-c/src/msgpack/type/fixint.hpp',
        '../../external/msgpack-c/src/msgpack/type/float.hpp',
        '../../external/msgpack-c/src/msgpack/type/int.hpp',
        '../../external/msgpack-c/src/msgpack/type/list.hpp',
        '../../external/msgpack-c/src/msgpack/type/map.hpp',
        '../../external/msgpack-c/src/msgpack/type/nil.hpp',
        '../../external/msgpack-c/src/msgpack/type/pair.hpp',
        '../../external/msgpack-c/src/msgpack/type/raw.hpp',
        '../../external/msgpack-c/src/msgpack/type/set.hpp',
        '../../external/msgpack-c/src/msgpack/type/string.hpp',
        '../../external/msgpack-c/src/msgpack/type/tuple.hpp',
        '../../external/msgpack-c/src/msgpack/type/vector.hpp',
        '../../external/msgpack-c/src/msgpack/type/tr1/unordered_map.hpp',
        '../../external/msgpack-c/src/msgpack/type/tr1/unordered_set.hpp',
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
