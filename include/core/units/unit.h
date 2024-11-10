#pragma once

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

using namespace godot;

/// @brief Class for length unit related constants and other unit helper methods
class LengthUnit : public RefCounted 
{
    GDCLASS(LengthUnit, RefCounted);
private:
    
public:
    LengthUnit() = default;
    ~LengthUnit() = default;
    static const int NOT_SET = -1;
    static const int PIXEL = 0;
    static const int PERCENTAGE = 1;
    static const int VIEWPORT_WIDTH = 2;
    static const int VIEWPORT_HEIGHT = 3;
protected:
    static void _bind_methods();
};

inline void LengthUnit::_bind_methods()
{
    BIND_CONSTANT(NOT_SET);
    BIND_CONSTANT(PIXEL);
    BIND_CONSTANT(PERCENTAGE);
    BIND_CONSTANT(VIEWPORT_WIDTH);
    BIND_CONSTANT(VIEWPORT_HEIGHT);
}

/// @brief Pair of unit type (from LengthUnit contants) and length
struct LengthPair{
    int unit_type;
    double length;
    LengthPair(int unit_type, double length);
    LengthPair() = default;

    /// @brief Gets a length pair from a string representation of that pair
    /// @param string_pair The string pair representation
    /// @return Converted length pair
    static LengthPair get_pair(String string_pair);

    /// @brief Gets a int unit from provided string unit representation;
    /// @param unit_string String unit representation
    /// @return Converted int unit
    static int get_unit(String unit_string);

    /// @brief Gets a string representation of length pair
    /// @param pair The pair length to convert
    /// @return Converted string pair
    static String get_pair_str(LengthPair pair);
};