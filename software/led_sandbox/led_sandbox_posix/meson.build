project(
    'led_sandbox_posix',
    ['c', 'cpp'],
    version : '0.1',
    default_options : ['cpp_std=c++20', 'b_lto=true'])

cc = meson.get_compiler('cpp')

sources = [
    'Src/main.c',
    'Src/led_sandbox_hal_impl_posix.cpp',
    '../led_sandbox_common/Src/led_sandbox.c',
    '../led_sandbox_common/Src/scheduler.c',
    '../led_sandbox_common/Src/state_machine_task.c',
    '../led_sandbox_common/Src/pixel_dust_task.cpp',
    '../led_sandbox_common/subprojects/Adafruit_PixelDust/Adafruit_PixelDust.cpp', 
]

incdir = include_directories('../led_sandbox_common/Inc/', '../led_sandbox_common/subprojects/Adafruit_PixelDust/')

executable('led_sandbox',
           sources,
           dependencies: [],
           include_directories : incdir,
           )

