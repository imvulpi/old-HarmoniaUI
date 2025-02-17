#!/usr/bin/env python
# For different architectures like 32bit, use arch=option
# For clearing use scons -c ext="extensions you want to remove from the src/ extern/godotcpp/"
import os
import sys

env = SConscript("./extern/godot-cpp/SConstruct")

# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

def get_files(paths: list[str], extensions: list[str], exclude: list[str]):
    collected_paths = []
    for path in paths:
        for root, dirs, files in os.walk(path):
            dirs[:] = [d for d in dirs if os.path.join(root, d) not in exclude]
            for file in files:
                for extension in extensions:
                    if file.endswith(extension):
                        collected_paths.append(os.path.join(root, file))
    return collected_paths

def remove_files(paths: list[str]):
    for path in paths:
        try: 
            os.remove(path) 
            print(f"File {path} successfully removed!") 
        except OSError as error: 
            print(error)
            print(f"File: {path} can not be removed.") 

def handle_cleaning():
    arguments = sys.argv
    clean_extensions = [".o", ".obj", ".os"]
    for argument in sys.argv:
        if(argument.startswith("extension=") or argument.startswith("e=") or argument.startswith("ext=")):
            argument = argument.split('=')[1] # Removes first = this way allows extensions with =
            extensions_str = argument.split(',')
            extensions = list(map(lambda ext: ext.strip(), extensions_str))
            print("Extensions:", "".join(f" {ext}" for ext in extensions))
    paths_to_clean = get_files(["./src", "./extern/godot-cpp"], clean_extensions, [])
    print(" ".join(f"Will remove: {ptc}\n" for ptc in paths_to_clean))
    should_clear = input("Continue? Y/n: ")
    if(should_clear.lower() == "y"):
        remove_files(paths_to_clean)
    else:
        sys.exit(0)
# Check if -c (clean) is passed
clean_mode = False
if '--clean=deep' in sys.argv or '-c=deep' in sys.argv:
    print("Clean mode")
    clean_mode = True
    handle_cleaning()
elif '-c' in sys.argv or '--clean' in sys.argv:
    print("Clean mode")
    clean_mode = True
else:
    print("Not in clean mode.")

env.Append(CPPPATH=['./include/', './src/'])
linker_flags = []
processed_linker_flags = []
processed_cxx_flags = []
processed_rm_cxx_flags = []
processed_rm_linker_flags = []
linker_flags = ARGUMENTS.get("f-link")
cxx_flags = ARGUMENTS.get('f-cxx')
rm_cxx_flags = ARGUMENTS.get('rmf-cxx')
rm_linker_flags = ARGUMENTS.get("rmf-link")
cpp_std = ARGUMENTS.get('std', 'c++17')
cpp_compiler = ARGUMENTS.get("cxx")
linker = ARGUMENTS.get("linker")
c_compiler = ARGUMENTS.get("cc")

if rm_cxx_flags is not None:
    rm_cxx_flags = str(rm_cxx_flags)

if rm_linker_flags is not None:
    rm_linker_flags = str(rm_linker_flags)

if cxx_flags is not None:
    cxx_flags = str(cxx_flags)

if linker_flags is not None:
    linker_flags = str(linker_flags)

# Resolve flags:
if (cpp_compiler != None):  
    env["CXX"] = cpp_compiler
else:
    cpp_compiler = env["CXX"]

if(linker != None):
    env["LINK"] = linker
else:
    linker = env["LINK"]

# Resolve flags:
if (c_compiler != None):
    env["CC"] = c_compiler
else:
    c_compiler = env["CC"]

if(linker_flags != None):
    linker_flags_split = linker_flags.split(',')
    for flag in linker_flags_split:
        processed_linker_flags.append(flag.strip())

if(rm_cxx_flags != None):
    rm_cxx_flags_split = rm_cxx_flags.split(',')
    for flag in rm_cxx_flags_split:
        processed_rm_cxx_flags.append(flag.strip())

if(rm_linker_flags != None):
    rm_linker_flags_split = rm_linker_flags.split(',')
    for flag in rm_linker_flags_split:
        processed_rm_linker_flags.append(flag.strip())

if(cxx_flags != None):
    cxx_flags_split = cxx_flags.split(',')
    for flag in cxx_flags_split:
        processed_cxx_flags.append(flag.strip())

# Removes C++ compiler flags (from rmf-cxx)
cxx_flags = env["CXXFLAGS"]
if(cxx_flags is not None):
    cxx_flags = str(cxx_flags)
    for flag in processed_rm_cxx_flags:
        cxx_flags = cxx_flags.replace(flag, "")
    env["CXXFLAGS"] = cxx_flags

# Removes C++ linker flags (from rmf-link)
t_linker_flags = env["LINKFLAGS"]
if(t_linker_flags is not None):
    t_linker_flags = str(t_linker_flags)
    for flag in processed_rm_linker_flags:
        t_linker_flags = t_linker_flags.replace(flag, "")
    env["LINKFLAGS"] = t_linker_flags

# Adds C++ compiler flags (from f-cxx)
t_cxx_flags = env["CXXFLAGS"]
if(t_cxx_flags is not None):
    t_cxx_flags = str(t_cxx_flags)
    for flag in processed_cxx_flags:
        t_cxx_flags += " " + flag
    env["CXXFLAGS"] = t_cxx_flags

# Adds C++ compiler flags (from f-link)
t_linker_flags = env["LINKFLAGS"]
if(t_linker_flags is not None):
    t_linker_flags = str(t_linker_flags)
    for flag in processed_linker_flags:
        t_linker_flags += " " + flag
    env["LINKFLAGS"] = t_linker_flags

# collects all .cpp files except "gen"
cpp_files = []
exclude = set(['src\\gen',])
for root, dirs, files in os.walk('src'):
    dirs[:] = [d for d in dirs if os.path.join(root, d) not in exclude]
    for file in files:
        if file.endswith('.cpp'):
            cpp_files.append(os.path.join(root, file))

sources = cpp_files

# Printing info:
if(clean_mode == False):
    print("\n-----\nBUILD SETTINGS:\n")
    print("Linker flags: ", ''.join(flag for flag in env["LINKFLAGS"]))
    print("C++ Compiler flags: ", ''.join(flag for flag in env["CXXFLAGS"]))
    if 'CXX' in env:
        print(f"C++ compiler: {env['CXX']}")
    if 'CC' in env:
        print(f"C compiler: {env['CC']}")
    if 'LINK' in env:
        print(f"Linker: {env['LINK']}")
    if 'SHLINK' in env:
        print(f"Shared Linker: {env['SHLINK']}")
    
    # Uncomment this if you encounter errors with Archiver/Ranlib (Usually Android Builds)
    # env['ARCOMSTR'] = 'AR COMMAND: $AR $ARFLAGS $TARGET $SOURCES'
    # env['RANLIBCOM'] = ''
    # env['ARFLAGS'] = 'rcs'
    # env["SHLINKCOMSTR"] = '$SHLINK -o $TARGET $SHLINKFLAGS $__SHLIBVERSIONFLAGS $__RPATH $SOURCES $_LIBDIRFLAGS $_LIBFLAGS'

    print("AR Tool:", env['AR'])
    print("AR FLAGS: ", env['ARFLAGS'])
    print("AR COMMAND: ", env["ARCOM"])
    print("SHLINK COMMAND: ", env["SHLINKCOM"])
    print("CXX COMMAND", env["CXXCOM"])

    print("\nLinking:")
    print(f"SHLINKFLAGS: {env.get('SHLINKFLAGS', 'No flags')}")
    print(f"LINKFLAGS: {env.get('LINKFLAGS', 'No flags')}")
    print("\n-----\n")

if env["target"] in ["editor", "template_debug"]:
    # Will create issues if you create more directories in doc_classes/
    doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
    sources.append(doc_data)

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "export/bin/harmoniaui.{}.{}.framework/harmoniaui.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
elif env["platform"] == "ios":
    if env["ios_simulator"]:
        library = env.StaticLibrary(
            "export/bin/harmoniaui.{}.{}.simulator.a".format(env["platform"], env["target"]),
            source=sources,
        )
    else:
        library = env.StaticLibrary(
            "export/bin/harmoniaui.{}.{}.a".format(env["platform"], env["target"]),
            source=sources,
        )
elif env["platform"] == "android":
    # Uncomment this if you encounter errors with Archiver/Ranlib (Usually Android Builds)
    # env['ARCOMSTR'] = 'AR COMMAND: $AR $ARFLAGS $TARGET $SOURCES'
    env['RANLIBCOM'] = ''
    env['ARFLAGS'] = 'rcs'
    env.Append(LIBS=['c++_shared', 'm', 'c', 'android']) # Required libraries for android build (need to be defined explicitly)
    # env["SHLINKCOMSTR"] = '$SHLINK -o $TARGET $SHLINKFLAGS $__SHLIBVERSIONFLAGS $__RPATH $SOURCES $_LIBDIRFLAGS $_LIBFLAGS'
    edited_link_flags = str(env.get('LINKFLAGS'))
    edited_link_flags = edited_link_flags.replace("-dead_strip", "")
    env["LINKFLAGS"] = edited_link_flags
    print("Removed -dead_strip from LINKFLAGS.")
    print("Edited LINKFLAGS: ", env["LINKFLAGS"])
    library = env.SharedLibrary(
        target="export/bin/harmoniaui{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "export/bin/harmoniaui{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
