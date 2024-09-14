if get_option('with_test').enabled()
    run_command(['python3', 'tools' / 'generate-runner.py'], check: true)

    test_src = ['unit_runner.c']
    test_cubes = [
        'cnullptr', 'command', 'memory', 'hostsys', 'arguments', 'regex'
    ]

    foreach cube : test_cubes
        test_src += ['test_' + cube + '.c']
    endforeach

    pizza = executable('runner', test_src,
        include_directories: dir,
        dependencies: [
            dependency('fossil-test'),
            fossil_lib_dep])

    test('xunit_tests', pizza)  # Renamed the test target for clarity
endif
