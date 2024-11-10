#pragma once

/// @brief A converter class for different unit types (pixel, percentage, viewport width, viewport height)
class UnitConverter
{  
public:
    UnitConverter() = default;
    ~UnitConverter() = default;
    static double px_to_percentage(double px, double base);
    static double px_to_vw(double px, double width);
    static double px_to_vh(double px, double height);
    static double vw_to_percentage(double vw, double window_width, double pct_base);
    static double vw_to_px(double vw, double width);
    static double vw_to_vh(double vw, double width, double height);
    static double vh_to_percentage(double vh, double window_height, double pct_base);
    static double vh_to_px(double vh, double height);
    static double vh_to_vw(double vh, double width, double height);
    static double percentage_to_vw(double percentage, double window_width, double pct_base);
    static double percentage_to_px(double percentage, double base);
    static double percentage_to_vh(double percentage, double window_height, double pct_base);
};

/// @brief pixel to percentage
/// @param px value
/// @param base base from which percentage should be calculated. (ex. container width)
/// @return percentage (format: 0.5 (written: 50%) (not 50))
inline double UnitConverter::px_to_percentage(double px, double base)
{
    return px/base;
}

/// @brief pixel value to vw value
/// @param px value
/// @param width width of the viewport
/// @return vw value (format: 50 (not 0.5))
inline double UnitConverter::px_to_vw(double px, double width)
{
    return px/width * 100;
}

/// @brief pixel value to vh value
/// @param px value
/// @param height height of the viewport
/// @return vh value (format: 50 (not 0.5))
inline double UnitConverter::px_to_vh(double px, double height)
{
    return px/height * 100;
}

/// @brief vw value to percentage value
/// @param vw value
/// @param window_width Viewport width
/// @param pct_base width from which percentage is calculated (ex. parent container)
/// @return percentage value from the pct_base
inline double UnitConverter::vw_to_percentage(double vw, double window_width, double pct_base)
{
    return vw/100 * window_width/pct_base;
}

/// @brief vw value to pixel value
/// @param vw value
/// @param width viewport width value
/// @return pixel value
inline double UnitConverter::vw_to_px(double vw, double width)
{
    return vw/100*width;
}

/// @brief vw value to vh value
/// @param vw value
/// @param width viewport width
/// @param height viewport height
/// @return vh value
inline double UnitConverter::vw_to_vh(double vw, double width, double height){
    return ((vw * width / 100) / height) * 100;
}

/// @brief vh value to percentage value
/// @param vh value
/// @param window_height Viewport height
/// @param pct_base height from which percentage is calculated (ex. parent container)
/// @return percentage value from the pct_base
inline double UnitConverter::vh_to_percentage(double vh, double window_height, double pct_base)
{
    return vh/100 * window_height/pct_base;
}

/// @brief vh value to pixel value
/// @param vh value
/// @param height viewport height
/// @return pixel value
inline double UnitConverter::vh_to_px(double vh, double height)
{
    return vh/100*height;
}

/// @brief vh value to vw value
/// @param vh value
/// @param width viewport width
/// @param height viewport height
/// @return vw value
inline double UnitConverter::vh_to_vw(double vh, double width, double height){
    return ((vh * height / 100) / width) * 100;
}

/// @brief percentage value to vw value
/// @param percentage value
/// @param window_width viewport width
/// @param pct_base width from which percentage was calculated (ex. parent container)
/// @return percentage value
inline double UnitConverter::percentage_to_vw(double percentage, double window_width, double pct_base)
{
    return (pct_base*percentage)/window_width*100;
}

/// @brief percentage value to px value
/// @param percentage value
/// @param base base from which the percentage was calculated.
/// @return percentage value
inline double UnitConverter::percentage_to_px(double percentage, double base)
{
    return base*percentage;
}

/// @brief percentage value to vh value
/// @param percentage value
/// @param window_height viewport height
/// @param pct_base height from which percentage was calculated.
/// @return percentage value
inline double UnitConverter::percentage_to_vh(double percentage, double window_height, double pct_base)
{
     return (pct_base*percentage)/window_height*100;
}
