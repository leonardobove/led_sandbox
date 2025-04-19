project('led_sandbox_posix', 'c',
  version : '0.1',
  default_options : [
    'b_lto=true'])

cc = meson.get_compiler('c')

sources = [
    'Src/main.c',
    'Src/led_sandbox_hal_impl_posix.c',
    '../led_sandbox_common/Src/led_sandbox.c',
    '../led_sandbox_common/Src/scheduler.c',
    '../led_sandbox_common/Src/state_machine_task.c'
]

incdir = include_directories('../led_sandbox_common/Inc/')

executable('led_sandbox',
           sources,
           dependencies: [],
           include_directories : incdir,
           )

