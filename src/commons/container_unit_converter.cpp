#include "commons/container_unit_converter.h"

double ContainerUnitConverter::get_width(LengthPair pair, double parent_width, Vector2i window_size, int unit_type)
{
    if(unit_type == Harmonia::Unit::PIXEL){
        return get_width_px(pair, parent_width, window_size);
    }else if(unit_type == Harmonia::Unit::PERCENTAGE){
        return get_width_percentage(pair, parent_width, window_size);
    }else if(unit_type == Harmonia::Unit::VIEWPORT_WIDTH){
        return get_width_vw(pair, parent_width, window_size);
    }else if(unit_type == Harmonia::Unit::VIEWPORT_HEIGHT){
        return get_width_vh(pair, parent_width, window_size);
    }else{
        return NULL;
    }
}

double ContainerUnitConverter::get_width_px(LengthPair pair, double parent_width, Vector2i window_size){
    if(pair.unit_type == Harmonia::Unit::PIXEL){
        return pair.length;
    }else if(pair.unit_type == Harmonia::Unit::PERCENTAGE){
        return percentage_to_px(pair.length, parent_width);
    }else if(pair.unit_type == Harmonia::Unit::VIEWPORT_WIDTH){
        return vw_to_px(pair.length, window_size.x);
    }else if(pair.unit_type == Harmonia::Unit::VIEWPORT_HEIGHT){
        return vh_to_px(pair.length, window_size.y);
    }else{
        return NULL;
    }
}

double ContainerUnitConverter::get_width_vw(LengthPair pair, double parent_width, Vector2i window_size){
    if(pair.unit_type == Harmonia::Unit::PIXEL){
        return px_to_vw(pair.length, window_size.x);
    }else if(pair.unit_type == Harmonia::Unit::PERCENTAGE){
        return percentage_to_vw(pair.length, window_size.x, parent_width);
    } else if(pair.unit_type == Harmonia::Unit::VIEWPORT_WIDTH){
        return pair.length;
    }else if(pair.unit_type == Harmonia::Unit::VIEWPORT_HEIGHT){
        return vh_to_vw(pair.length, window_size.x, window_size.y);
    }else{
        return NULL;
    }
}

double ContainerUnitConverter::get_width_vh(LengthPair pair, double parent_width, Vector2i window_size){
    if(pair.unit_type == Harmonia::Unit::PIXEL){
        return px_to_vh(pair.length, window_size.y);
    }else if(pair.unit_type == Harmonia::Unit::PERCENTAGE){
        return percentage_to_vh(pair.length, window_size.y, parent_width);
    }else if(pair.unit_type == Harmonia::Unit::VIEWPORT_WIDTH){
        return vw_to_vh(pair.length, window_size.x, window_size.y);
    }else if(pair.unit_type == Harmonia::Unit::VIEWPORT_HEIGHT){
        return pair.length;
    }else{
        return NULL;
    }
}

double ContainerUnitConverter::get_width_percentage(LengthPair pair, double parent_width, Vector2i window_size){
    if(pair.unit_type == Harmonia::Unit::PIXEL){
        return px_to_percentage(pair.length, parent_width);
    }else if(pair.unit_type == Harmonia::Unit::PERCENTAGE){
        return pair.length;
    }else if(pair.unit_type == Harmonia::Unit::VIEWPORT_WIDTH){
        return vw_to_percentage(pair.length, window_size.x, parent_width);
    }else if(pair.unit_type == Harmonia::Unit::VIEWPORT_HEIGHT){
        return vh_to_percentage(pair.length, window_size.y, parent_width);
    }else{
        return NULL;
    }
}

double ContainerUnitConverter::get_height(LengthPair pair, double parent_height, Vector2i window_size, int unit_type){
    if(unit_type == Harmonia::Unit::PIXEL){
        return get_height_px(pair, parent_height, window_size);
    }else if(unit_type == Harmonia::Unit::PERCENTAGE){
        return get_height_percentage(pair, parent_height, window_size);
    }else if(unit_type == Harmonia::Unit::VIEWPORT_WIDTH){
        return get_height_vw(pair, parent_height, window_size);
    }else if(unit_type == Harmonia::Unit::VIEWPORT_HEIGHT){
        return get_height_vh(pair, parent_height, window_size);
    }else{
        return NULL;
    }
}

double ContainerUnitConverter::get_height_px(LengthPair pair, double parent_height, Vector2i window_size){
    if(pair.unit_type == Harmonia::Unit::PIXEL){
        return pair.length;
    }else if(pair.unit_type == Harmonia::Unit::PERCENTAGE){
        return percentage_to_px(pair.length, parent_height);
    }else if(pair.unit_type == Harmonia::Unit::VIEWPORT_WIDTH){
        return vw_to_px(pair.length, window_size.x);
    }else if(pair.unit_type == Harmonia::Unit::VIEWPORT_HEIGHT){
        return vh_to_px(pair.length, window_size.y);
    }else{
        return NULL;
    }
}

double ContainerUnitConverter::get_height_vw(LengthPair pair, double parent_height, Vector2i window_size){
    if(pair.unit_type == Harmonia::Unit::PIXEL){
        return px_to_vw(pair.length, window_size.x);
    }else if(pair.unit_type == Harmonia::Unit::PERCENTAGE){
        return percentage_to_vw(pair.length, window_size.x, parent_height);
    } else if(pair.unit_type == Harmonia::Unit::VIEWPORT_WIDTH){
        return pair.length;
    }else if(pair.unit_type == Harmonia::Unit::VIEWPORT_HEIGHT){
        return vh_to_vw(pair.length, window_size.x, window_size.y);
    }else{
        return NULL;
    }
}

double ContainerUnitConverter::get_height_vh(LengthPair pair, double parent_height, Vector2i window_size){
    if(pair.unit_type == Harmonia::Unit::PIXEL){
        return px_to_vh(pair.length, window_size.y);
    }else if(pair.unit_type == Harmonia::Unit::PERCENTAGE){
        return percentage_to_vh(pair.length, window_size.y, parent_height);
    }else if(pair.unit_type == Harmonia::Unit::VIEWPORT_WIDTH){
        return vw_to_vh(pair.length, window_size.x, window_size.y);
    }else if(pair.unit_type == Harmonia::Unit::VIEWPORT_HEIGHT){
        return pair.length;
    }else{
        return NULL;
    }
}

double ContainerUnitConverter::get_height_percentage(LengthPair pair, double parent_height, Vector2i window_size){
    if(pair.unit_type == Harmonia::Unit::PIXEL){
        return px_to_percentage(pair.length, parent_height);
    }else if(pair.unit_type == Harmonia::Unit::PERCENTAGE){
        return pair.length;
    }else if(pair.unit_type == Harmonia::Unit::VIEWPORT_WIDTH){
        return vw_to_percentage(pair.length, window_size.x, parent_height);
    }else if(pair.unit_type == Harmonia::Unit::VIEWPORT_HEIGHT){
        return vh_to_percentage(pair.length, window_size.y, parent_height);
    }else{
        return NULL;
    }
}