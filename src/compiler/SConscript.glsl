import common

Import('*')

from sys import executable as python_cmd

env = env.Clone()

env.MSVC2013Compat()

env.Prepend(CPPPATH = [
    '#include',
    '#src',
    '#src/mapi',
    '#src/mesa',
    '#src/gallium/include',
    '#src/gallium/auxiliary',
    '#src/compiler/glsl',
    '#src/compiler/glsl/glcpp',
])

env.Prepend(LIBS = [mesautil])

# Make glcpp-parse.h and glsl_parser.h reachable from the include path.
env.Prepend(CPPPATH = [Dir('.').abspath, Dir('glsl').abspath])

glcpp_env = env.Clone()
glcpp_env.Append(YACCFLAGS = [
    '-d',
    '-p', 'glcpp_parser_'
])

glsl_env = env.Clone()
glsl_env.Append(YACCFLAGS = [
    '--defines=%s' % File('glsl/glsl_parser.h').abspath,
    '-p', '_mesa_glsl_',
])

# without this line scons will expect "glsl_parser.hpp" instead of
# "glsl_parser.h", causing glsl_parser.cpp to be regenerated every time
glsl_env['YACCHXXFILESUFFIX'] = '.h'

glcpp_lexer = glcpp_env.CFile('glsl/glcpp/glcpp-lex.c', 'glsl/glcpp/glcpp-lex.l')
glcpp_parser = glcpp_env.CFile('glsl/glcpp/glcpp-parse.c', 'glsl/glcpp/glcpp-parse.y')
glsl_lexer = glsl_env.CXXFile('glsl/glsl_lexer.cpp', 'glsl/glsl_lexer.ll')
glsl_parser = glsl_env.CXXFile('glsl/glsl_parser.cpp', 'glsl/glsl_parser.yy')

# common generated sources
glsl_sources = [
    glcpp_lexer,
    glcpp_parser[0],
    glsl_lexer,
    glsl_parser[0],
] 

# parse Makefile.sources
source_lists = env.ParseSourceList('Makefile.sources')

# add non-generated sources
for l in ('LIBGLCPP_FILES', 'LIBGLSL_FILES'):
    glsl_sources += source_lists[l]

if env['msvc']:
    env.Prepend(CPPPATH = ['#/src/getopt'])
    env.PrependUnique(LIBS = [getopt])

# Copy these files to avoid generation object files into src/mesa/program
env.Prepend(CPPPATH = ['#src/mesa/main'])
env.Command('glsl/imports.c', '#src/mesa/main/imports.c', Copy('$TARGET', '$SOURCE'))
# Copy these files to avoid generation object files into src/mesa/program
env.Prepend(CPPPATH = ['#src/mesa/program'])
env.Command('glsl/prog_hash_table.c', '#src/mesa/program/prog_hash_table.c', Copy('$TARGET', '$SOURCE'))
env.Command('glsl/symbol_table.c', '#src/mesa/program/symbol_table.c', Copy('$TARGET', '$SOURCE'))
env.Command('glsl/dummy_errors.c', '#src/mesa/program/dummy_errors.c', Copy('$TARGET', '$SOURCE'))

compiler_objs = env.StaticObject(source_lists['GLSL_COMPILER_CXX_FILES'])

mesa_objs = env.StaticObject([
    'glsl/imports.c',
    'glsl/prog_hash_table.c',
    'glsl/symbol_table.c',
    'glsl/dummy_errors.c',
])

compiler_objs += mesa_objs

glsl = env.ConvenienceLibrary(
    target = 'glsl',
    source = glsl_sources,
)

# SCons builtin dependency scanner doesn't detect that glsl_lexer.ll depends on
# glsl_parser.h
env.Depends(glsl, glsl_parser)

Export('glsl')

# Skip building these programs as they will cause SCons error "Two environments
# with different actions were specified for the same target"
if env['crosscompile'] or env['embedded']:
    Return()

env = env.Clone()

if env['platform'] == 'windows':
    env.PrependUnique(LIBS = [
        'user32',
    ])

env.Prepend(LIBS = [compiler, glsl])

compiler_objs += env.StaticObject("glsl/main.cpp")

glsl_compiler = env.Program(
    target = 'glsl_compiler',
    source = compiler_objs,
)
env.Alias('glsl_compiler', glsl_compiler)

glcpp = env.Program(
    target = 'glsl/glcpp/glcpp',
    source = ['glsl/glcpp/glcpp.c'] + mesa_objs,
)
env.Alias('glcpp', glcpp)
