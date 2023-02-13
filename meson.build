project('screenload-sg', 'c',
          version: '0.1.0',
    meson_version: '>= 0.50.0',
  default_options: [ 'warning_level=2',
                     'c_std=c99',
                   ],
)

glib_req_version = '>= 2.35.1'
gtk_req_version = '>= 3.12.0'

glib_dep = dependency('glib-2.0', version: glib_req_version)
gtk_dep = dependency('gtk+-3.0', version: gtk_req_version)

subdir('src')
