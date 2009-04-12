env = Environment()
env.Export('env')
env.MergeFlags([
    '!fltk-config --cxxflags --ldflags',
])
env.SConscript('tests/SConscript')
env.SConscript('src/SConscript', variant_dir='build', duplicate=0)

# vim: ft=python
