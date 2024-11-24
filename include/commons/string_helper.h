#pragma once

#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

/// @brief Replaces all instances of a string inside of another string to another string.
/// @param str Original string with all instances
/// @param replace String instances to replace
/// @param to String to replace string instances with
/// @return String with replaced strings to another string
String replace(String str, String replace, String to);