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

/// @brief Retrieves a number from a string, ends search when encounters a character not from a number. 
/// @param str String from which number should be retrieved
/// @param readable_chars Should chars which improve numbers clarity/readability be allowed/skipped/ignored? (ex. 100.00.0 or 100.00'0), note: space isnt a readable char.
/// @param implied_zero Is zero implied in case where first character is a dot (.)? (ex. .45 = 0.45);
/// @param stopped_index A number of an index when the retrieval stopped due to a invalid character.
/// @return A new string which includes all retrieved numbers, or empty if number is invalid.
String get_string_number(String str, bool readable_chars = true, bool implied_zero = true, int* stopped_index = nullptr);