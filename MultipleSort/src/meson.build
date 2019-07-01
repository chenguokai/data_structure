multiplesort_sources = [
  'main.vala',
  'window.vala',
]

multiplesort_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
]

gnome = import('gnome')

multiplesort_sources += gnome.compile_resources('multiplesort-resources',
  'multiplesort.gresource.xml',
  c_name: 'multiplesort'
)

executable('multiplesort', multiplesort_sources,
  vala_args: '--target-glib=2.50',  dependencies: multiplesort_deps,
  install: true,
)
