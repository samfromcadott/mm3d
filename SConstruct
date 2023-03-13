import os
from os.path import join, dirname

LIBS=['raylib', 'opengl32', 'gdi32', 'winmm']
LIBPATH='./lib'

CXXFLAGS='-static --target=x86_64-w64-windows-gnu -std=c++17'
LINKFLAGS = '--target=x86_64-w64-windows-gnu -static-libgcc -static-libstdc++'

VariantDir('build', 'src', duplicate=False)
env = Environment(
	CXX='clang++',
	CPPPATH=['./include'],
	tools = ['mingw'],
	ENV = {'PATH' : os.environ['PATH']},
	LIBS=LIBS,
	LIBPATH=LIBPATH,
	CXXFLAGS=CXXFLAGS,
	LINKFLAGS=LINKFLAGS
)
env['ENV']['TERM'] = os.environ['TERM'] # Colored output

source = [ Glob('build/*.cc') ]
env.Program('bin/mm3d.exe', source)
