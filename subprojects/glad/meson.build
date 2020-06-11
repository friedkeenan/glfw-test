project('glad', 'c')

dl_dep = meson.get_compiler('c').find_library('dl')

inc = include_directories('include')

sources = []

subdir('source')

lib = static_library('glad', sources,
    include_directories : inc,
    dependencies        : dl_dep,
)