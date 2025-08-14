project('CXML', 'c',
        default_options: [ 'c_std=c23', 'warning_level=3' ],
        license: 'GPL-3.0-or-later',
        version: '0.0.3')

add_project_arguments([
    '-DAPP_NAME="'    + meson.project_name()    + '"',
    '-DAPP_VERSION="' + meson.project_version() + '"',
], language: 'c')


add_project_dependencies([
    dependency('libcjson'),
], language: 'c')


include_dirs = include_directories('include', '.')
subdir('src')