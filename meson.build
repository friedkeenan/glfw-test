project('glfw-test', 'cpp')

inc = []

fried_proj = subproject('libfried')
fried_lib = fried_proj.get_variable('lib')
inc += fried_proj.get_variable('inc')

sources = []
subdir('source')

executable('glfw-test', sources,
    include_directories : inc,
    link_with           : [fried_lib],

    cpp_args : [
        '-fno-exceptions',
        '-Wall',
        '-Werror',
        '-std=gnu++20',
    ],
)