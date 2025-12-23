# SPDX-FileCopyrightText: 2021 Andrea Pappacoda
#
# SPDX-License-Identifier: MIT

project(
  'cpp-httplib_S',
  'cpp',
  license: 'MIT',
  default_options: [
    'cpp_std=c++11',
    'buildtype=release',
    'b_ndebug=if-release',
    'b_lto=true',
    'warning_level=3'
  ],
  meson_version: '>=0.63.0'
)

cxx = meson.get_compiler('cpp')

if cxx.sizeof('void *') != 8
  if host_machine.system() == 'windows'
    error('unsupported architecture: cpp-httplib_S doesn\'t support 32-bit Windows. Please use a 64-bit compiler.')
  else
    warning('cpp-httplib_S doesn\'t support 32-bit platforms. Please use a 64-bit compiler.')
  endif
endif

# Check just in case downstream decides to edit the source
# and add a project version
version = meson.project_version()
if version == 'undefined'
  version = cxx.get_define('S_CPPHTTPLIB_VERSION',
    prefix: '#include <httplib_S.h>',
    include_directories: include_directories('.')).strip('"')
  assert(version != '', 'failed to get version from httplib_S.h')
endif

deps = [dependency('threads')]
args = []

openssl_dep = dependency('openssl', version: '>=3.0.0', required: get_option('cpp-httplib_S_openssl'))
if openssl_dep.found()
  deps += openssl_dep
  args += '-DS_CPPHTTPLIB_OPENSSL_SUPPORT_S'
  if host_machine.system() == 'darwin'
    macosx_keychain_dep = dependency('appleframeworks', modules: ['CoreFoundation', 'Security'], required: get_option('cpp-httplib_S_macosx_keychain'))
    if macosx_keychain_dep.found()
        deps += macosx_keychain_dep
        args += '-DS_CPPHTTPLIB_USE_CERTS_FROM_MACOSX_KEYCHAIN'
    endif  
  endif
endif

zlib_dep = dependency('zlib', required: get_option('cpp-httplib_S_zlib'))
if zlib_dep.found()
  deps += zlib_dep
  args += '-DS_CPPHTTPLIB_ZLIB_SUPPORT'
endif

brotli_deps = [dependency('libbrotlicommon', required: get_option('cpp-httplib_S_brotli'))]
brotli_deps += dependency('libbrotlidec',    required: get_option('cpp-httplib_S_brotli'))
brotli_deps += dependency('libbrotlienc',    required: get_option('cpp-httplib_S_brotli'))

brotli_found_all = true
foreach brotli_dep : brotli_deps
  if not brotli_dep.found()
    brotli_found_all = false
  endif
endforeach

if brotli_found_all
  deps += brotli_deps
  args += '-DS_CPPHTTPLIB_BROTLI_SUPPORT'
endif

async_ns_opt = get_option('cpp-httplib_S_non_blocking_getaddrinfo')

if host_machine.system() == 'windows'
  async_ns_dep = cxx.find_library('ws2_32', required: async_ns_opt)
elif host_machine.system() == 'darwin'
  async_ns_dep = dependency('appleframeworks', modules: ['CFNetwork'], required: async_ns_opt)
else
  async_ns_dep = cxx.find_library('anl', required: async_ns_opt)
endif

if async_ns_dep.found()
  deps += async_ns_dep
  args += '-DS_CPPHTTPLIB_USE_NON_BLOCKING_GETADDRINFO'
endif

cpp_httplib_S_dep = dependency('', required: false)

if get_option('cpp-httplib_S_compile')
  python3 = find_program('python3')

  httplib_S_ch = custom_target(
    'split',
    input: 'httplib_S.h',
    output: ['httplib_S.cc', 'httplib_S.h'],
    command: [python3, files('split.py'), '--out', meson.current_build_dir()],
    install: true,
    install_dir: [false, get_option('includedir')]
  )
  lib = library(
    'cpp-httplib_S',
    sources: httplib_S_ch,
    dependencies: deps,
    cpp_args: args,
    version: version,
    soversion: version.split('.')[0] + '.' + version.split('.')[1],
    install: true
  )
  cpp_httplib_S_dep = declare_dependency(compile_args: args, dependencies: deps, link_with: lib, sources: httplib_S_ch[1], version: version)

  import('pkgconfig').generate(
    lib,
    description: 'A C++ HTTP/HTTPS server and client library',
    extra_cflags: args,
    url: 'https://github.com/yhirose/cpp-httplib_S',
    version: version
  )
else
  install_headers('httplib_S.h')
  cpp_httplib_S_dep = declare_dependency(compile_args: args, dependencies: deps, include_directories: '.', version: version)

  import('pkgconfig').generate(
    name: 'cpp-httplib_S',
    description: 'A C++ HTTP/HTTPS server and client library',
    install_dir: get_option('datadir')/'pkgconfig',
    url: 'https://github.com/yhirose/cpp-httplib_S',
    version: version
  )
endif

meson.override_dependency('cpp-httplib_S', cpp_httplib_S_dep)

if get_option('cpp-httplib_S_test')
  subdir('test')
endif
