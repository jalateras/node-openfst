{
    "variables": {
        "openfst_home_linux": "/usr/local",
        "openfst_home_win": "C:/Software/openfst",
        "openfst_home_mac": "/usr/local",
        "module_name": "openfst",
        "module_path": "./lib/binding/",
    },
    'targets': [
        {
            'target_name': 'openfst',
            'conditions': [
            ['OS=="linux"', {
                'cflags!': [ '-fno-exceptions' ],
                'cflags_cc!': [ '-fno-exceptions' ],
                'cflags': ['-fPIC', "-O4", "-std=c++14", "-fexceptions"],
                'include_dirs': [
                    'src',
                    '<!(node -e "require(\'nan\')")',
                    '<(openfst_home_linux)/include'
                ],
                'sources': [
                    '<!@(find src -name "src/*.cc")'
                ],
                'link_settings': {
                    'libraries': [
                        '-lfst'
                    ],
                    'ldflags': [
                        '-L<(openfst_home_linux)/lib'
                    ]
                }
            }],
            ['OS=="win"', {
                'include_dirs': [
                    'src',
                    '<!(node -e "require(\'nan\')")',
                    '<(openfst_home_win)/include',
                    './win/include',
                    './src',
                    'C:/Software/node-v0.12.7/src',
                    'C:/Program Files/Microsoft SDKs/Windows/v7.1/Include'
                ],
                'sources': [
                    '<!@(find src -name "*.cc")'
                ],
                'msbuild_toolset': 'v120',
                "configurations": {
                            "Release": {
                    'msvs_settings':
                    {
                        'VCCLCompilerTool':
                        {
                            'RuntimeLibrary': 2,        # shared release
                            'ExceptionHandling': 1,     # /EHsc
                            'AdditionalOptions':
                            [
                                '/EHsc' # Enable unwind semantics for Exception Handling.  This one actually does the trick - and no warning either.
                            ]
                        },
                        'VCLinkerTool':
                        {
                            'AdditionalOptions':
                            [
                                '/FORCE:MULTIPLE'
                            ]
                        }
                    }
                }
                },
                'link_settings': {
                    'libraries': [
                        '<(openfst_home_win)/lib/fst.lib'
                    ]
                }
            }],
            ['OS=="mac"', {
                'cflags!': [ '-fno-exceptions' ],
                'cflags_cc!': [ '-fno-exceptions' ],
                'cflags': ['-fPIC', "-O4", "-std=c++14", "-fexceptions"],
                'xcode_settings': {
                    'OTHER_CPLUSPLUSFLAGS': ["-fPIC", "-O3", "-std=c++14", "-fexceptions","-v", "-stdlib=libc++", "-Werror"],
                    'OTHER_LDFLAGS': [],
                    'MACOSX_DEPLOYMENT_TARGET': '10.10'
                },
                'include_dirs': [
                    'src',
                    '<!(node -e "require(\'nan\')")',
                    '<(openfst_home_mac)/include'
                ],
                'sources': [
                    '<!@(find src -name "module.cc")'
                ],
                'libraries': [
                    '<(openfst_home_mac)/lib/libfst.dylib'
                ],
                'link_settings': {
                    'libraries': [
                        '<(openfst_home_mac)/lib/libfst.dylib'
                    ],
                    'ldflags': [
                        '-L<(openfst_home_mac)/lib'
                    ]
                }
            }]
          ]
        },
        {
            "target_name": "action_after_build",
            "type": "none",
            "dependencies": [ "<(module_name)" ],
            "copies": [
            {
              "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
              "destination": "<(module_path)"
            }
            ]
        }

    ]
}
