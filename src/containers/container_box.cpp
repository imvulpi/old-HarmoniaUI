#include "containers/container_box.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/project_settings.hpp>

void ContainerBox::_ready(){
    set_process(true);
}

void ContainerBox::_process(double time) {
    update_time += time;
    if(update_time >= update_interval){
        bool is_editor = Engine::get_singleton()->is_editor_hint();
        if (Engine::get_singleton()->is_editor_hint()) {
            editor_update_presentation();
        }
        else {
            update_presentation();
        }
        update_time -= update_interval;
    }
}

void ContainerBox::update_presentation(){
    // Updates self size
    Vector2 new_size = Vector2(get_width(), get_height());
    ContainerBox::set_size(new_size);
}

void ContainerBox::editor_update_presentation(){
    // Updates self size
    Vector2 new_size = Vector2(editor_get_width(), editor_get_height());
    ContainerBox::set_size(new_size);
}

void ContainerBox::set_debug_outputs(bool debug_outputs)
{
    ContainerBox::debug_outputs = debug_outputs;
}

bool ContainerBox::get_debug_outputs()
{
    return ContainerBox::debug_outputs;
}

double ContainerBox::get_width(int unit_type){
    if(width_str != ""){
        width = LengthPair::get_pair(width_str);
    }

    if(unit_type == LengthUnit::NOT_SET) return 0;
    
    Size2 window_size = get_tree()->get_root()->get_visible_rect().size;
    if(parent == nullptr){
        return ContainerUnitConverter::get_width(width, window_size.x, window_size, unit_type);
    }

    return ContainerUnitConverter::get_width(width, parent->get_width(), window_size, unit_type);
}

void ContainerBox::set_width(double length, int unit_type){
    ContainerBox::width.length = length;
    ContainerBox::width.unit_type = unit_type;
}

double ContainerBox::editor_get_width(int unit_type)
{
    if(height_str != ""){
        height = LengthPair::get_pair(height_str);
    }
    if(unit_type == LengthUnit::NOT_SET) return 0;

    Size2 window_size = Size2(
        ProjectSettings::get_singleton()->get_setting("display/window/size/viewport_width"), 
        ProjectSettings::get_singleton()->get_setting("display/window/size/viewport_height"));

    if(parent == nullptr){
        return ContainerUnitConverter::get_width(width, window_size.x, window_size, unit_type);
    }

    return ContainerUnitConverter::get_width(width, parent->get_width(), window_size, unit_type);
}

void ContainerBox::set_width_str(String length_and_unit){
    width_str = length_and_unit;
    width = LengthPair::get_pair(length_and_unit);
}

String ContainerBox::get_width_str()
{
    return width_str;
}

void ContainerBox::set_height(double length, int unit_type){
    ContainerBox::height.length = length;
    ContainerBox::height.unit_type = unit_type;
}

void ContainerBox::set_height_str(String length_and_unit){
    height_str = length_and_unit; 
    height = LengthPair::get_pair(length_and_unit);
}

String ContainerBox::get_height_str()
{
    return height_str;
}

double ContainerBox::get_height(int unit_type){
    if(unit_type == LengthUnit::NOT_SET) return 0;

    Size2 window_size = get_tree()->get_root()->get_visible_rect().size;

    if(parent == nullptr){
        Size2 window_size = get_tree()->get_root()->get_visible_rect().size;
        return ContainerUnitConverter::get_height(height, window_size.y, window_size, unit_type);
    }

    return ContainerUnitConverter::get_height(height, parent->get_height(), window_size, unit_type);
}

double ContainerBox::editor_get_height(int unit_type)
{    
    if(unit_type == LengthUnit::NOT_SET) return 0;

    Size2 window_size = Size2(
        ProjectSettings::get_singleton()->get_setting("display/window/size/viewport_width"), 
        ProjectSettings::get_singleton()->get_setting("display/window/size/viewport_height"));

    if(parent == nullptr){
        return ContainerUnitConverter::get_height(height, window_size.y, window_size, unit_type);
    }

    return ContainerUnitConverter::get_height(height, parent->get_height(), window_size, unit_type);
}

void ContainerBox::_bind_methods(){
    ClassDB::bind_method(D_METHOD("set_width", "length", "unit_type"), &ContainerBox::set_width);
    ClassDB::bind_method(D_METHOD("get_width", "unit_type"), &ContainerBox::get_width);
    ClassDB::bind_method(D_METHOD("set_height", "length", "unit_type"), &ContainerBox::set_height);
    ClassDB::bind_method(D_METHOD("get_height", "unit_type"), &ContainerBox::get_height);

    ClassDB::bind_method(D_METHOD("set_width_str", "length_and_unit"), &ContainerBox::set_width_str);
    ClassDB::bind_method(D_METHOD("get_width_str"), &ContainerBox::get_width_str);    
    ClassDB::bind_method(D_METHOD("set_height_str", "length_and_unit"), &ContainerBox::set_height_str);
    ClassDB::bind_method(D_METHOD("get_height_str"), &ContainerBox::get_height_str);

    ClassDB::bind_method(D_METHOD("set_debug_outputs", "debug_outputs"), &ContainerBox::set_debug_outputs);
    ClassDB::bind_method(D_METHOD("get_debug_outputs"), &ContainerBox::get_debug_outputs);
}

bool ContainerBox::_set(const StringName &p_name, const Variant &p_value)
{
    String name = p_name;
	if (name == "width_str") {
		set_width_str(p_value);
		return true;
	}else if(name == "height_str"){
        set_height_str(p_value);
        return true;
    }else if(name == "debug_outputs"){
        set_debug_outputs(p_value);
    	return true;
    }
	return false;
}

bool ContainerBox::_get(const StringName &p_name, Variant &r_ret) const
{
    String name = p_name;
	if (name == "width_str") {
	    r_ret = width_str;
		return true;
	}else if(name == "height_str"){
        r_ret = height_str;
        return true;
    }else if(name == "debug_outputs"){
        r_ret = debug_outputs;
    	return true;
    }
	return false;
}

void ContainerBox::_get_property_list(List<PropertyInfo> *p_list) const
{
    p_list->push_back(PropertyInfo(Variant::STRING, "width_str"));
    p_list->push_back(PropertyInfo(Variant::STRING, "height_str"));
    p_list->push_back(PropertyInfo(Variant::BOOL, "debug_outputs"));
}
