shader_sources = files(
    'triangle.vert',
    'triangle.frag',
)

cmd = [files('process.py'),
    '--out-dir',    '@OUTDIR@',
    '--source-dir', meson.current_source_dir(),
    '@INPUT@',
]

sources += custom_target('shaders',
    input   : shader_sources,
    output  : 'shaders',
    command : cmd,

    build_by_default : true,
)