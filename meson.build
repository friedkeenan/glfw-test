project('glfw-test', 'cpp')

inc = []

fried_proj = subproject('libfried')
fried_lib = fried_proj.get_variable('lib')
fried_pch = 'subprojects/libfried/' + fried_proj.get_variable('pch')
inc += fried_proj.get_variable('inc')

sources = []
subdir('source')

subdir('shaders')

executable('glfw-test', sources,
    include_directories : inc,
    link_with           : fried_lib,

    link_args : '-s',
    cpp_pch   : fried_pch,
    cpp_args  : [
        '-fno-exceptions',
        '-Wall',
        '-Werror',
        '-std=gnu++20',
    ],
)