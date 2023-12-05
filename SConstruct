import os
from os.path import join, dirname
import shutil
import subprocess

LIBS=['raylib', 'opengl32', 'gdi32', 'winmm']
LIBPATH='./lib'

CXXFLAGS='-static --target=x86_64-w64-windows-gnu -std=c++17'
LINKFLAGS = '--target=x86_64-w64-windows-gnu -static-libgcc -static-libstdc++ -mwindows'

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

# Web environment
target = 'wasm32-unknown-emscripten'

VariantDir('build/web', 'src', duplicate=False)
web_env = Environment(
	CC="emcc",
	CXX="em++",
	# TOOLS=TOOLS,
	CPPPATH=['include/web'],
	ENV = {'PATH' : os.environ['PATH']},
	LIBS=['raylib'],
	LIBPATH=['lib/web'],
	CCFLAGS = f'--target={target} -static -Wno-unknown-warning-option -Wunused-variable -O3',
	CXXFLAGS=f'--target={target} -static -std=c++20 -Wno-unknown-warning-option -Wunused-variable -O3 -Wno-unqualified-std-cast-call -D BRUTUS_CHUNK_SIZE=32',
	LINKFLAGS=f'--target={target} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY --preload-file assets -s ALLOW_MEMORY_GROWTH --shell-file shell.html',
	PROGSUFFIX='.html'
)
web_env['ENV']['TERM'] = os.environ['TERM'] # Colored output

web_source = [ Glob('build/web/*.cc') ]
web_env.Program('output/index', web_source)

subprocess.call( [ '7za', 'u', 'mm3d-win.zip', 'assets', './bin/*' ] ) # Put the files in an archive
subprocess.call( [ '7za', 'u', 'mm3d-web.zip', './output/*' ] ) # Put the files in an archive
