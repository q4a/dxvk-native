util_src = [
  'util_env.cpp',
  'util_fps_limiter.cpp',
  'util_matrix.cpp',
  'util_monitor.cpp',
  
  'com/com_guid.cpp',
  'com/com_private_data.cpp',

  'config/config.cpp',
  
  'log/log.cpp',
  'log/log_debug.cpp',
  
  'sha1/sha1.c',
  'sha1/sha1_util.cpp',

  'sync/sync_recursive.cpp',
]

util_src_win32 = [
  'util_gdi.cpp',

  'platform/util_luid_win32.cpp',
  'platform/util_env_win32.cpp',
  'platform/util_string_win32.cpp'
]

util_src_linux = [
  'platform/util_luid_linux.cpp',
  'platform/util_env_linux.cpp',
  'platform/util_string_linux.cpp',
  'platform/thread_native.cpp',
]

util_src_darwin = [
  'platform/util_luid_linux.cpp',
  'platform/util_env_darwin.cpp',
  'platform/util_string_linux.cpp',
  'platform/thread_native.cpp',
]

if dxvk_platform == 'windows'
  util_src += util_src_win32
elif dxvk_platform == 'linux'
  util_src += util_src_linux
elif dxvk_platform == 'darwin'
  util_src += util_src_darwin
else
  error('Unknown platform for util')
endif

util_lib = static_library('util', util_src,
  include_directories : [ dxvk_include_path ],
  override_options    : ['cpp_std='+dxvk_cpp_std])

util_dep = declare_dependency(
  link_with           : [ util_lib ])
