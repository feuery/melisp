import os
import glob

env = Environment(ENV = {'PATH' : os.environ['PATH']})
SOURCES = glob.glob('src/c/*.cpp')
HEADERS = glob.glob('src/headers/*.h')

env.Append(CCFLAGS = ['-g', '-Wall', '-std=c++11', '-Isrc/headers/'])

# env.Append(LIBS = [# 'SDL2_gfx',
#                    'SDL2_ttf'])

env.Program(target = 'bin/main', source = SOURCES)
