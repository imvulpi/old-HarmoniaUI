#include "core/units/unit.h"
#include "commons/string_helper.h"

LengthPair::LengthPair(int unit_type, double length)
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
    int unit = get_unit(unit_string);

    // Converts into an actual float percentage
    if(unit == LengthUnit::PERCENTAGE){
        value = value/100;
    }

    return LengthPair(unit, value);
}

String LengthPair::get_pair_str(LengthPair pair){
    String pair_str;
    pair_str += String::num(pair.length);
    switch (pair.unit_type)
    {
        case LengthUnit::PIXEL:
            pair_str += "px";
            break;
        case LengthUnit::PERCENTAGE:
            pair_str += "%";
            break;
        case LengthUnit::VIEWPORT_WIDTH:
            pair_str += "vw";
            break;
        case LengthUnit::VIEWPORT_HEIGHT:
            pair_str += "vh";
            break;
        default:
            return pair_str + pair.unit_type;
    }

    return pair_str;
}

int LengthPair::get_unit(String unit_string){
    if(unit_string == "px"){
        return LengthUnit::PIXEL;
    }else if(unit_string == "%"){
        return LengthUnit::PERCENTAGE;
    }else if(unit_string == "vh"){
        return LengthUnit::VIEWPORT_HEIGHT;
    }else if(unit_string == "vw"){
        return LengthUnit::VIEWPORT_WIDTH;
    }else{
        return LengthUnit::NOT_SET;
    }
}
