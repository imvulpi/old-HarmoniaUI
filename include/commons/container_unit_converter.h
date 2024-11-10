#pragma once

#include "commons/unit_converter.h"
#include "core/units/unit.h"

/// @brief A wrapper unit converter for easy use in containers.
class ContainerUnitConverter : UnitConverter
{
public:
    ContainerUnitConverter();
    ~ContainerUnitConverter();
    
    /// @brief Gets width in any unit type from any correct length pair.
    /// @param pair Length and unit
    /// @param parent_width Width of the parent container
    /// @param window_size Root viewport size
    /// @param unit_type Type of the returning width from Length::Unit (default PIXEL)
    /// @return Width in the provided unit type
    static double get_width(LengthPair pair, double parent_width, Vector2i window_size, int unit_type = LengthUnit::PIXEL);
    
    /// @brief Gets width in pixels from any correct length pair.
    /// @param pair Length and unit
    /// @param parent_width Width of the parent container
    /// @param window_size Root viewport size
    /// @return Width in pixels
    static double get_width_px(LengthPair pair, double parent_width, Vector2i window_size);

    /// @brief Gets width in vw (viewport width) from any correct length pair.
    /// @param pair Length and unit
    /// @param parent_width Width of the parent container
    /// @param window_size Root viewport size
    /// @return Width in vw
    static double get_width_vw(LengthPair pair, double parent_width, Vector2i window_size);

    /// @brief Gets width in vh (viewport height) from any correct length pair.
    /// @param pair Length and unit
    /// @param parent_width Width of the parent container
    /// @param window_size Root viewport size
    /// @return Width in vh
    static double get_width_vh(LengthPair pair, double parent_width, Vector2i window_size);

    /// @brief Gets width in % (percentage) from any correct length pair.
    /// @param pair Length and unit
    /// @param parent_width Width of the parent container
    /// @param window_size Root viewport size
    /// @return Width in %/pct
    static double get_width_percentage(LengthPair pair, double parent_width, Vector2i window_size);
    
    /// @brief Gets height in any unit type from any correct length pair.
    /// @param pair Length and unit
    /// @param parent_height Height of the parent container
    /// @param window_size Root viewport size
    /// @param unit_type Type of the returning height from Length::Unit (default PIXEL)
    /// @return height in the provided unit type
    static double get_height(LengthPair pair, double parent_height, Vector2i window_size, int unit_type = LengthUnit::PIXEL);
    
    /// @brief Gets height in pixels from any correct length pair.
    /// @param pair Length and unit
    /// @param parent_height Height of the parent container
    /// @param window_size Root viewport size
    /// @return Height in pixels
    static double get_height_px(LengthPair pair, double parent_height, Vector2i window_size);

    /// @brief Gets height in vw (viewport height) from any correct length pair.
    /// @param pair Length and unit
    /// @param parent_height Height of the parent container
    /// @param window_size Root viewport size
    /// @return Height in vw
    static double get_height_vw(LengthPair pair, double parent_height, Vector2i window_size);

    /// @brief Gets height in vh (viewport height) from any correct length pair.
    /// @param pair Length and unit
    /// @param parent_height Height of the parent container
    /// @param window_size Root viewport size
    /// @return Height in vh
    static double get_height_vh(LengthPair pair, double parent_height, Vector2i window_size);

    /// @brief Gets height in % (percentage) from any correct length pair.
    /// @param pair Length and unit
    /// @param parent_height Height of the parent container
    /// @param window_size Root viewport size
    /// @return Height in %/pct
    static double get_height_percentage(LengthPair pair, double parent_height, Vector2i window_size);
};
