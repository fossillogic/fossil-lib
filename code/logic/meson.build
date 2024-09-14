dir = include_directories('.')

fossil_lib_lib = library('fossil-lib',
    files('command.c', 'memory.c', 'hostsys.c', 'arguments.c', 'regex.c'),
    install: true,
    dependencies: [dependency('threads')], # needed for regex threading features
    include_directories: dir)

fossil_lib_dep = declare_dependency(
    link_with: [fossil_lib_lib],
    dependencies: [dependency('threads')],
    include_directories: dir)
