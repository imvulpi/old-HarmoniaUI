#include "containers/container_box.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include "core/systems/alert/layout/alert_layout_change.h"

void ContainerBox::_ready(){
    set_process(true);
}

void ContainerBox::_process(double time) {
    if(debug_outputs) UtilityFunctions::print("[GLOBAL] Current Time: ", update_time, " Interval: ", update_interval);
    update_time += time;
    if(update_time >= update_interval){
        if(debug_outputs) UtilityFunctions::print("[GLOBAL] bind amounts: ", alert_manager->binds.size());
        if (Engine::get_singleton()->is_editor_hint()) {
            editor_update_presentation();
        }
        else {
            update_presentation();
        }
        update_time -= update_interval;
    }
}

void ContainerBox::_gui_input(const Ref<InputEvent> &p_gui_input)
{
    ERR_FAIL_COND(p_gui_input.is_null());

    if(auto* mouse_event = Object::cast_to<InputEventMouseButton>(*p_gui_input)){
        if(mouse_event->is_pressed()){
            if(mouse_event->get_button_index() == MouseButton::MOUSE_BUTTON_WHEEL_UP){

            }
        }
    }
}

AlertManager* ContainerBox::get_alert_manager(){
    return alert_manager;
}

void ContainerBox::set_alert_manager(AlertManager* manager){
    alert_manager = manager;
}

void ContainerBox::update_presentation(){
    if(parent == nullptr){
        parent = get_parent_container();
    }

    // Updates self size
    Vector2 new_size = Vector2(get_width(), get_height());
    if(debug_outputs) UtilityFunctions::print("[RUNTIME] New size: ", new_size);
    ContainerBox::set_size(new_size);
}

void ContainerBox::editor_update_presentation(){
    if(parent == nullptr){
        parent = get_parent_container();
    }

    // Updates self size
    Vector2 new_size = Vector2(editor_get_width(), editor_get_height());
    if(debug_outputs) UtilityFunctions::print("[EDITOR] New size: ", new_size);
    ContainerBox::set_size(new_size);
}

ContainerBox* ContainerBox::get_parent_container()
{
    Node* parent_node = get_parent();
    if(auto* container_box = Object::cast_to<ContainerBox>(parent_node))
    {
        return container_box;
    }

    return nullptr;
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
    if(debug_outputs) UtilityFunctions::print("[RUNTIME] Width: ", width.length, " ", width.unit_type);

    Size2 window_size = get_tree()->get_root()->get_visible_rect().size;
    if(parent == nullptr){
        return ContainerUnitConverter::get_width(width, window_size.x, window_size, unit_type);
    }

    return ContainerUnitConverter::get_width(width, parent->get_width(), window_size, unit_type);
}

void ContainerBox::set_width(double length, int unit_type){
    ContainerBox::width.length = length;
    ContainerBox::width.unit_type = unit_type;
    alert_manager->dispatch_alert(&AlertLayoutChange(ALERT_LAYOUT_CHANGE, AlertLayoutChange::LayoutChanged::WIDTH));
}

double ContainerBox::editor_get_width(int unit_type)
{
    if(height_str != ""){
        height = LengthPair::get_pair(height_str);
    }

    if(unit_type == LengthUnit::NOT_SET) return 0;
    if(debug_outputs) UtilityFunctions::print("[EDITOR] Width: ", width.length, " ", width.unit_type);

    Size2 window_size = Size2(
        ProjectSettings::get_singleton()->get_setting("display/window/size/viewport_width"), 
        ProjectSettings::get_singleton()->get_setting("display/window/size/viewport_height"));

    if(parent == nullptr){
        return ContainerUnitConverter::get_width(width, window_size.x, window_size, unit_type);
    }

    return ContainerUnitConverter::get_width(width, parent->editor_get_width(), window_size, unit_type);
}

void ContainerBox::set_width_str(String length_and_unit){
    width_str = length_and_unit;
    LengthPair pair = LengthPair::get_pair(length_and_unit);
    set_width(pair.length, pair.unit_type);
}

String ContainerBox::get_width_str()
{
    return width_str;
}

void ContainerBox::set_height(double length, int unit_type){
    ContainerBox::height.length = length;
    ContainerBox::height.unit_type = unit_type;
    alert_manager->dispatch_alert(&AlertLayoutChange(ALERT_LAYOUT_CHANGE, AlertLayoutChange::LayoutChanged::HEIGHT));
}

void ContainerBox::set_height_str(String length_and_unit){
    height_str = length_and_unit; 
    LengthPair pair = LengthPair::get_pair(length_and_unit);
    set_height(pair.length, pair.unit_type);
}

String ContainerBox::get_height_str()
{
    return height_str;
}

double ContainerBox::get_height(int unit_type){
    if(unit_type == LengthUnit::NOT_SET) return 0;
    if(debug_outputs) UtilityFunctions::print("[RUNTIME] Width: ", width.length, " ", width.unit_type);

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
    if(debug_outputs) UtilityFunctions::print("[EDITOR] Height: ", width.length, " ", width.unit_type);

    Size2 window_size = Size2(
        ProjectSettings::get_singleton()->get_setting("display/window/size/viewport_width"), 
        ProjectSettings::get_singleton()->get_setting("display/window/size/viewport_height"));

    if(parent == nullptr){
        return ContainerUnitConverter::get_height(height, window_size.y, window_size, unit_type);
    }

    return ContainerUnitConverter::get_height(height, parent->editor_get_height(), window_size, unit_type);
}

void ContainerBox::_notification(int p_what)
{
    if(p_what == NOTIFICATION_READY){
        _ready();
    }else if(p_what == NOTIFICATION_PROCESS){
        _process(get_process_delta_time());
    }
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

    ClassDB::bind_method(D_METHOD("set_alert_manager", "manager"), &ContainerBox::set_alert_manager);
    ClassDB::bind_method(D_METHOD("get_alert_manager"), &ContainerBox::get_alert_manager);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "alert_manager", PROPERTY_HINT_RESOURCE_TYPE, "alert_manager"), "set_alert_manager", "get_alert_manager");
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
