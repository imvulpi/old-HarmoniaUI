#pragma once

#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/templates/list.hpp>

using namespace godot;

/// @brief Replaces all instances of a string inside of another string to another string.
/// @param str Original string with all instances
/// @param replace String instances to replace
/// @param to String to replace string instances with
/// @return String with replaced strings to another string
String replace(String str, String replace, String to);

/// @brief Splits the string into a list by the given seperator.
/// @param str Original string to be split
/// @param seperator The seperator that should be used to split the string.
/// @param ignore_empty Should empty split results be ignored? 
/// @return A list of all strings split by a seperator.
List<String> split(String str, String seperator, bool ignore_empty = true);