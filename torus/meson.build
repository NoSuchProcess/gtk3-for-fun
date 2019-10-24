project('gtk3gl', 'c', version: '1.0')
add_project_arguments(['-Wno-unused-parameter'], language: 'c')

ld = find_program('ld')
shaders_gen = generator(ld, output: '@BASENAME@.o', arguments: ['--format', 'binary', '--relocatable', '--output', '@OUTPUT@', '@INPUT@'])
shaders = shaders_gen.process(
    'shader/container.vertex.glsl', 'shader/container.fragment.glsl',
    'shader/light.vertex.glsl', 'shader/light.fragment.glsl'
)

glmath_inc = include_directories('../../glmath')

m_dep = meson.get_compiler('c').find_library('m', required: false)
gtk_dep = dependency('gtk+-3.0', version: '>= 3.16')
gdk_pixbuf_dep = dependency('gdk-pixbuf-2.0', version: '>= 2.32')
glib_dep = dependency('glib-2.0')
epoxy_dep = dependency('epoxy')

executable('gtk3gl',
    ['main.c', 'shader_compile.c', 'shader_make.c', shaders],
    include_directories: [glmath_inc],
    dependencies: [m_dep, gtk_dep, gdk_pixbuf_dep, glib_dep, epoxy_dep]
)
