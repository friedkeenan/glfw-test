project('libfried', 'cpp',
    version         : '0.0.1',
    license         : 'GPL2',
)

inc = [include_directories('include')]

glad_proj = subproject('glad')
glad_lib = glad_proj.get_variable('lib')
inc += glad_proj.get_variable('inc')

glfw_dep = dependency('glfw3')

sources = []
subdir('source')

lib = static_library('fried', sources,
    include_directories : inc,
    dependencies        : [glfw_dep],
    link_with           : [glad_lib],

    cpp_args : [
        '-fno-exceptions',
        '-Wall',
        '-Werror',
        '-std=gnu++20',
    ],
)