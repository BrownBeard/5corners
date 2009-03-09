env = Environment()
env.Export('env')
env.MergeFlags([
    '!fltk-config --cxxflags --ldflags',
])
env.SConscript([
    'tests/SConscript',
])

# vim: ft=python
