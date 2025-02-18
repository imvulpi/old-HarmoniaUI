#!/usr/bin/env python
# For different architectures like 32bit, use arch=option
# For clearing use scons -c ext="extensions you want to remove from the src/ extern/godotcpp/"
# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

import os
import sys

ARGUMENT_SET_C_COMPILER = "cc"
ARGUMENT_SET_CXX_CPP_COMPILER = "cxx"
ARGUMENT_SET_LINKER = "linker"
ARGUMENT_REMOVE_LINKER_FLAGS = "rmf-link"
ARGUMENT_REMOVE_CXX_CPP_FLAGS = "rmf-cxx"
ARGUMENT_ADD_LINKER_FLAGS = "f-link"
ARGUMENT_ADD_CXX_FLAGS = "f-cxx"

env = SConscript("./extern/godot-cpp/SConstruct")

def normalize_paths(paths: list[str]):
    for i in range(0, len(paths)):
        paths[i] = os.path.normpath(paths[i])

def get_files(paths: list[str], extensions: list[str], exclude_paths: list[str]):
    collected_paths = []
    normalize_paths(paths)
    normalize_paths(exclude_paths)
    for path in paths:
        for root, dirs, files in os.walk(path):
            dirs[:] = [d for d in dirs if os.path.join(root, d) not in exclude_paths]
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

def process_string_argument(argument):
    if argument is not None:
        return str(argument)

def process_argument_list(argument_str: (str | None), seperator=','):
    if(argument_str != None):
        processed_arguments: list[str] = []
        arguments = argument_str.split(seperator)
        for argument in arguments:
            processed_arguments.append(argument.strip())
        return processed_arguments

def remove_values_env_var(env_variable_name: str, remove_values: (list[str] | None)):
    env_values = env[env_variable_name]
    if((env_values is not None) and (remove_values is not None)):
        env_values = str(env_values)
        for value in remove_values:
            env_values = env_values.replace(value, "")
        env[env_variable_name] = env_values

def add_values_env_var(env_variable_name: str, add_values: (list[str] | None)):
    env_values = env[env_variable_name]
    if((env_values is not None) and (add_values is not None)):
        env_values = str(env_values)
        for value in add_values:
            env_values += " " + value
        env[env_variable_name] = env_values

def handle_cleaning():
    clean_extensions = [".o", ".obj", ".os"]
    for argument in sys.argv:
        if(argument.startswith("extension=") or argument.startswith("e=") or argument.startswith("ext=")):
            argument = argument.split('=')[1] # Removes just the first '=', that allows extensions with =
            extensions = process_argument_list(argument)
            print("Extensions:", "".join(f" {ext}" for ext in extensions))
    paths_to_clean = get_files(["./src", "./extern/godot-cpp"], clean_extensions, [])
    print(" ".join(f"Will remove: {path_to_clean}\n" for path_to_clean in paths_to_clean))
    should_clear = input("Continue? Y/n: ")
    if(should_clear.lower() == "y"):
        remove_files(paths_to_clean)
    else:
        sys.exit(0)

def handle_flags():
    linker_flags = process_string_argument(ARGUMENTS.get(ARGUMENT_ADD_LINKER_FLAGS))
    cxx_flags = process_string_argument(ARGUMENTS.get(ARGUMENT_ADD_CXX_FLAGS))
    rm_cxx_flags = process_string_argument(ARGUMENTS.get(ARGUMENT_REMOVE_CXX_CPP_FLAGS))
    rm_linker_flags = process_string_argument(ARGUMENTS.get(ARGUMENT_REMOVE_LINKER_FLAGS))
    processed_linker_flags = process_argument_list(linker_flags)
    processed_cxx_flags = process_argument_list(cxx_flags)
    processed_rm_cxx_flags = process_argument_list(rm_cxx_flags)
    processed_rm_linker_flags = process_argument_list(rm_linker_flags)
    add_values_env_var("LINKFLAGS", processed_linker_flags)
    add_values_env_var("CXXFLAGS", processed_cxx_flags)
    remove_values_env_var("LINKFLAGS", processed_rm_linker_flags)
    remove_values_env_var("CXXFLAGS", processed_rm_cxx_flags)

def handle_setting_cpp_compiler():
    cpp_compiler = ARGUMENTS.get(ARGUMENT_SET_CXX_CPP_COMPILER)
    if (cpp_compiler != None):  
        env["CXX"] = cpp_compiler

def handle_setting_c_compiler():
    c_compiler = ARGUMENTS.get(ARGUMENT_SET_C_COMPILER)
    if (c_compiler != None):
        env["CC"] = c_compiler

def handle_setting_linker():
    linker = ARGUMENTS.get(ARGUMENT_SET_LINKER)
    if(linker != None):
        env["LINK"] = linker

def check_and_deep_clean() -> bool:
    """Checks if should deep clean, returns bool whether is in any cleaning mode"""
    if '--clean=deep' in sys.argv or '-c=deep' in sys.argv:
        print("Deep clean mode")
        handle_cleaning()
        return True
    elif '-c' in sys.argv or '--clean' in sys.argv:
        print("Clean mode")
        return True
    else:
        print("Not in clean mode.")

def print_debug_info():
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

    print("AR Tool:", env['AR'])
    print("AR FLAGS: ", env['ARFLAGS'])
    print("AR COMMAND: ", env["ARCOM"])
    print("SHLINK COMMAND: ", env["SHLINKCOM"])
    print("CXX COMMAND", env["CXXCOM"])

    print("\nLinking:")
    print(f"SHLINKFLAGS: {env.get('SHLINKFLAGS', 'No flags')}")
    print(f"LINKFLAGS: {env.get('LINKFLAGS', 'No flags')}")
    print("\n-----\n")

cleaning = check_and_deep_clean()
if(not cleaning):
    handle_setting_cpp_compiler()
    handle_setting_c_compiler()
    handle_setting_linker()
    handle_flags()
    print_debug_info()
    env.Append(CPPPATH=['./include/', './src/'])
    sources = get_files(['./src'], ['.cpp'], ['./src/gen/']) # collects all .cpp files except in gen directory
    print("".join(f"{source}\n" for source in sources))

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
        env.Append(LIBS=['c++_shared', 'm', 'c', 'android']) # Required libraries for android build (need to be defined explicitly)
        env['ARCOMSTR'] = 'AR COMMAND: $AR $ARFLAGS $TARGET $SOURCES'
        env['RANLIBCOM'] = ''
        env['ARFLAGS'] = 'rcs'
        env["SHLINKCOMSTR"] = '$SHLINK -o $TARGET $SHLINKFLAGS $__SHLIBVERSIONFLAGS $__RPATH $SOURCES $_LIBDIRFLAGS $_LIBFLAGS'
        print("Removing -dead_strip from LINKFLAGS.")
        remove_values_env_var("LINKFLAGS", ['-dead_strip'])
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
