#pragma once

#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

/// @brief Constants, enums and other related to HarmoniaUI project, This class shouldn't be an instance.
class Harmonia : public Object
{
    GDCLASS(Harmonia, Object);
public:
    Harmonia() = default;
    ~Harmonia() = default;

    /// @brief Enum used for defining overflowing behaviour
    enum OverflowBehaviour {
        SCROLL, // Will add scrolls and hide overflowing content
        HIDDEN, // Will hide overflowing content
        VISIBLE, // Overflowing content will be visible.
    };

    /// @brief Enum used for positioning of containers.
    enum Position { 
        STATIC,   // Normal
        ABSOLUTE, // Positioned to parent
        RELATIVE, // Positioned from the original location
    };

    /// @brief Enum used for visibility of containers
    enum Visibility {
        OBJECT_VISIBLE, // Visible container
        OBJECT_HIDDEN, // Hidden container no space allocated
        OBJECT_TRANSPARENT // Transparent container, space allocated but not visible
    };

    /// @brief Enum of units that are supported by specific length and other values.
    enum Unit {
        /// @brief Represents an unset unit.
        NOT_SET = -1,
        /// @brief This is a pixel unit, written short 'px' in values, ex: '100px'
        PIXEL,
        /// @brief This is a percentage unit, written short '%' in values, ex: '10%'
        PERCENTAGE,
        /// @brief This is a viewport width unit, written short 'vw' in values, ex: '10vw'
        VIEWPORT_WIDTH,
        /// @brief This is a viewport height unit, written short 'vh' in values, ex: '10vh'
        VIEWPORT_HEIGHT,
    };

    //const static String ALERT_LAYOUT_CHANGE; // "layout-change"
protected:
    static void _bind_methods();
};

/// @brief Pair containing unit of value and value/length.
///
/// Used in classes where Harmonia units are supported.
struct LengthPair{
    /// @brief The unit of the value
    ///
    /// For simpliticy of calculations: % are actual precentages in length ex. 10% is 0.1
    Harmonia::Unit unit_type {Harmonia::Unit::NOT_SET};
    
    /// @brief The value - length of the pair
    double length {0};

    /// @brief Constructs a Length pair with existing unit and length
    /// @param unit_type The unit of the value/length
    /// @param length The value - length of the pair, (% should be in percentage form ex. 0.1 is 10%)
    LengthPair(Harmonia::Unit unit_type, double length);
    LengthPair() = default;

    /// @brief Gets a length pair from a string representation of that pair
    /// @param string_pair The string pair representation
    /// @return Converted length pair
    static LengthPair get_pair(String string_pair);

    /// @brief Gets a int unit from provided string unit representation;
    /// @param unit_string String unit representation
    /// @return Converted int unit
    static Harmonia::Unit get_unit(String unit_string);

    /// @brief Gets a string representation of length pair
    /// @param pair The pair length to convert
    /// @return Converted string pair
    static String get_pair_str(LengthPair pair);
};

VARIANT_ENUM_CAST(Harmonia::OverflowBehaviour)
VARIANT_ENUM_CAST(Harmonia::Position)
VARIANT_ENUM_CAST(Harmonia::Unit)
VARIANT_ENUM_CAST(Harmonia::Visibility)