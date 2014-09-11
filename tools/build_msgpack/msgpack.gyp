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
        '../../external/msgpack-c/src/objectc.c',
        '../../external/msgpack-c/src/unpack.c',
        '../../external/msgpack-c/src/version.c',
        '../../external/msgpack-c/src/vrefbuffer.c',
        '../../external/msgpack-c/src/zone.c',
        '../../external/msgpack-c/src/object.cpp',
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
