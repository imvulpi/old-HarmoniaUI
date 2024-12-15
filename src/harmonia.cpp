#include "core/harmonia.h"
#include <godot_cpp/core/class_db.hpp>
#include "commons/string_helper.h"

using namespace godot;

LengthPair::LengthPair(Harmonia::Unit unit_type, double length)
{
    LengthPair::unit_type = unit_type;
    LengthPair::length = length;
}

LengthPair LengthPair::get_pair(String string_pair){
    string_pair = replace(string_pair, " ", "");
    String value_string;
    String unit_string;

    for (size_t i = 0; i < string_pair.length(); i++)
    {
        if (string_pair[i] == '0' || string_pair[i] == '1' || string_pair[i] == '2' || string_pair[i] == '3' || 
            string_pair[i] == '4' || string_pair[i] == '5' || string_pair[i] == '6' || string_pair[i] == '7' || 
            string_pair[i] == '8' || string_pair[i] == '9' || string_pair[i] == '.') {
            value_string += string_pair[i];
        } else {
            unit_string += string_pair[i];
        }
    }

    double value = value_string.to_float();
    Harmonia::Unit unit = get_unit(unit_string);

    // Converts into an actual float percentage
    if(unit == Harmonia::Unit::PERCENTAGE){
        value = value/100;
    }

    return LengthPair(unit, value);
}

String LengthPair::get_pair_str(LengthPair pair){
    String pair_str;
    pair_str += String::num(pair.length);
    switch (pair.unit_type)
    {
        case Harmonia::Unit::PIXEL:
            pair_str += "px";
            break;
        case Harmonia::Unit::PERCENTAGE:
            pair_str += "%";
            break;
        case Harmonia::Unit::VIEWPORT_WIDTH:
            pair_str += "vw";
            break;
        case Harmonia::Unit::VIEWPORT_HEIGHT:
            pair_str += "vh";
            break;
        default:
            return pair_str + pair.unit_type;
    }

    return pair_str;
}

Harmonia::Unit LengthPair::get_unit(String unit_string){
    if(unit_string == "px"){
        return Harmonia::Unit::PIXEL;
    }else if(unit_string == "%"){
        return Harmonia::Unit::PERCENTAGE;
    }else if(unit_string == "vh"){
        return Harmonia::Unit::VIEWPORT_HEIGHT;
    }else if(unit_string == "vw"){
        return Harmonia::Unit::VIEWPORT_WIDTH;
    }else{
        return Harmonia::Unit::NOT_SET;
    }
}

//const String Harmonia::ALERT_LAYOUT_CHANGE = "layout-change";

void Harmonia::_bind_methods(){
    BIND_ENUM_CONSTANT(SCROLL);
    BIND_ENUM_CONSTANT(HIDDEN);
    BIND_ENUM_CONSTANT(VISIBLE);

    BIND_ENUM_CONSTANT(STATIC);
    BIND_ENUM_CONSTANT(ABSOLUTE);
    BIND_ENUM_CONSTANT(RELATIVE);

    BIND_ENUM_CONSTANT(NOT_SET);
    BIND_ENUM_CONSTANT(PIXEL);
    BIND_ENUM_CONSTANT(PERCENTAGE);
    BIND_ENUM_CONSTANT(VIEWPORT_WIDTH);
    BIND_ENUM_CONSTANT(VIEWPORT_HEIGHT);
}