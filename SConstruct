#!/usr/bin/env python
import os

env = SConscript("./extern/godot-cpp/SConstruct")

# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# collects all .cpp files except "gen"
cpp_files = []
exclude = set(['src\\gen',])
for root, dirs, files in os.walk('src'):
    dirs[:] = [d for d in dirs if os.path.join(root, d) not in exclude]
    for file in files:
        if file.endswith('.cpp'):
            cpp_files.append(os.path.join(root, file))

env.Append(CPPPATH=['./include/', './src/'])
sources = cpp_files

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
else:
    library = env.SharedLibrary(
        "export/bin/harmoniaui{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
