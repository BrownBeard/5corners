env = Environment()
env.Export('env')
env.MergeFlags([
    '!fltk-config --cxxflags --ldflags',
    '-g',
])
env.VariantDir('build', 'src', duplicate = 0)
env.SConscript([
    'build/SConscript',
    'tests/SConscript',
])

# vim: ft=python
