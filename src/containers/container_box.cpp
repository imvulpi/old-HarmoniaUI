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
    update_time += time;
    if(update_time >= update_interval){
        if (Engine::get_singleton()->is_editor_hint()) {
            editor_update_presentation();
        }
        else {
            update_presentation();
        }
        update_time -= update_interval;
    }
}

/// TODO: Handling of scrolling inside this function
void ContainerBox::_gui_input(const Ref<InputEvent> &p_gui_input)
{
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
    
    Vector2 new_size = Vector2(get_width(), get_height());
    if(debug_outputs) UtilityFunctions::print("[RUNTIME] New size: ", new_size);
    ContainerBox::set_size(new_size);
    update_children_position(get_children());
}

void ContainerBox::update_children_position(TypedArray<Node> children){
    Vector2 position = Vector2(0, 0);
    // Add margin, padding - Future update.
    
    for (size_t i = 0; i < children.size(); i++)
    {
        auto current_child = children[i];
        if(auto* container = Object::cast_to<ContainerBox>(current_child)){
            if(container->position_type == Position::STATIC){
                container->set_position(position);
                position.y += container->get_height();
            }else if(container->position_type == Position::ABSOLUTE){
                container->set_position(Vector2(container->get_pos_x(), container->get_pos_y()));
            }else if(container-> position_type == Position::RELATIVE){
                container->set_position(Vector2(position.x + container->get_pos_x(), position.y + container->get_pos_y()));
                position.y += container->editor_get_height();
            }
        }else if(auto* control = Object::cast_to<Control>(current_child)){
            control->set_position(position);
            position.y += control->get_size().y;
        }
    }
}

void ContainerBox::editor_update_presentation(){
    if(parent == nullptr){
        parent = get_parent_container();
    }

    Vector2 new_size = Vector2(editor_get_width(), editor_get_height());
    if(debug_outputs) UtilityFunctions::print("[EDITOR] New size: ", new_size);
    ContainerBox::set_size(new_size);
    editor_update_children_position(get_children());
}

void ContainerBox::editor_update_children_position(TypedArray<Node> children)
{
    Vector2 position = Vector2(0, 0);
    // Add margin, padding - Future update.
    
    for (size_t i = 0; i < children.size(); i++)
    {
        auto current_child = children[i];
        if(auto* container = Object::cast_to<ContainerBox>(current_child)){
            if(container->position_type == Position::STATIC){
                container->set_position(position);
                position.y += container->editor_get_height();
            }else if(container->position_type == Position::ABSOLUTE){
                container->set_position(Vector2(container->editor_get_pos_x(), container->editor_get_pos_y()));
            }else if(container-> position_type == Position::RELATIVE){
                container->set_position(Vector2(position.x + container->editor_get_pos_x(), position.y + container->editor_get_pos_y()));
                position.y += container->editor_get_height();
            }
        }else if(auto* control = Object::cast_to<Control>(current_child)){
            control->set_position(position);
            position.y += control->get_size().y;
        }
    }
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

void ContainerBox::set_position_type(Position new_type){
    position_type = new_type;
}

ContainerBox::Position ContainerBox::get_position_type(){
    return position_type;
}

void ContainerBox::set_pos_x(double new_x, Harmonia::Unit unit_type){
    pos_x.length = new_x;
    pos_x.unit_type = unit_type;
    alert_manager->dispatch_alert(memnew(AlertLayoutChange(ALERT_LAYOUT_CHANGE, AlertLayoutChange::LayoutChanged::POSITION)));
}

double ContainerBox::get_pos_x(Harmonia::Unit unit_type){
    if(unit_type == Harmonia::Unit::NOT_SET) return 0;
    if(debug_outputs) UtilityFunctions::print("[RUNTIME] Pos x: ", pos_x.length, " ", pos_x.unit_type);

    Size2 window_size = get_tree()->get_root()->get_visible_rect().size;

    if(parent == nullptr){
        Size2 window_size = get_tree()->get_root()->get_visible_rect().size;
        return ContainerUnitConverter::get_width(pos_x, window_size.x, window_size, unit_type);
    }

    return ContainerUnitConverter::get_width(pos_x, parent->get_width(), window_size, unit_type);
}

double ContainerBox::editor_get_pos_x(Harmonia::Unit unit_type){
    if(unit_type == Harmonia::Unit::NOT_SET) return 0;
    if(debug_outputs) UtilityFunctions::print("[EDITOR] Pos x: ", pos_x.length, " ", pos_x.unit_type);

    Size2 window_size = Size2(
        ProjectSettings::get_singleton()->get_setting("display/window/size/viewport_width"), 
        ProjectSettings::get_singleton()->get_setting("display/window/size/viewport_height"));

    if(parent == nullptr){
        return ContainerUnitConverter::get_width(pos_x, window_size.x, window_size, unit_type);
    }

    return ContainerUnitConverter::get_width(pos_x, parent->editor_get_width(), window_size, unit_type);
}

void ContainerBox::set_pos_x_str(String new_x){
    pos_x_str = new_x;
    LengthPair pos_x = LengthPair::get_pair(new_x);
    set_pos_x(pos_x.length, pos_x.unit_type);
}

String ContainerBox::get_pos_x_str(){
    return pos_x_str;
}

void ContainerBox::set_pos_y(double new_y, Harmonia::Unit unit_type){
    pos_y.length = new_y;
    pos_y.unit_type = unit_type;
    alert_manager->dispatch_alert(memnew(AlertLayoutChange(ALERT_LAYOUT_CHANGE, AlertLayoutChange::LayoutChanged::POSITION)));
}

double ContainerBox::get_pos_y(Harmonia::Unit unit_type){
    if(unit_type == Harmonia::Unit::NOT_SET) return 0;
    if(debug_outputs) UtilityFunctions::print("[RUNTIME] Pos y: ", pos_y.length, " ", pos_y.unit_type);

    Size2 window_size = get_tree()->get_root()->get_visible_rect().size;

    if(parent == nullptr){
        return ContainerUnitConverter::get_height(pos_y, window_size.y, window_size, unit_type);
    }

    return ContainerUnitConverter::get_height(pos_y, parent->get_height(), window_size, unit_type);
}

double ContainerBox::editor_get_pos_y(Harmonia::Unit unit_type){
    if(unit_type == Harmonia::Unit::NOT_SET) return 0;
    if(debug_outputs) UtilityFunctions::print("[EDITOR] Pos y: ", pos_y.length, " ", pos_y.unit_type);

    Size2 window_size = Size2(
        ProjectSettings::get_singleton()->get_setting("display/window/size/viewport_width"), 
        ProjectSettings::get_singleton()->get_setting("display/window/size/viewport_height"));

    if(parent == nullptr){
        return ContainerUnitConverter::get_width(pos_y, window_size.y, window_size, unit_type);
    }

    return ContainerUnitConverter::get_width(pos_y, parent->editor_get_height(), window_size, unit_type);
}

void ContainerBox::set_pos_y_str(String new_y){
    pos_y_str = new_y;
    LengthPair pos_y = LengthPair::get_pair(new_y);
    set_pos_y(pos_y.length, pos_y.unit_type);
}

String ContainerBox::get_pos_y_str(){
    return pos_y_str;
}

void ContainerBox::set_debug_outputs(bool debug_outputs)
{
    ContainerBox::debug_outputs = debug_outputs;
}

bool ContainerBox::get_debug_outputs()
{
    return ContainerBox::debug_outputs;
}

double ContainerBox::get_width(Harmonia::Unit unit_type){
    if(unit_type == Harmonia::Unit::NOT_SET) return 0;
    if(debug_outputs) UtilityFunctions::print("[RUNTIME] Width: ", width.length, " ", width.unit_type);

    Size2 window_size = get_tree()->get_root()->get_visible_rect().size;
    if(parent == nullptr){
        return ContainerUnitConverter::get_width(width, window_size.x, window_size, unit_type);
    }

    return ContainerUnitConverter::get_width(width, parent->get_width(), window_size, unit_type);
}

void ContainerBox::set_width(double length, Harmonia::Unit unit_type){
    ContainerBox::width.length = length;
    ContainerBox::width.unit_type = unit_type;
    alert_manager->dispatch_alert(memnew(AlertLayoutChange(ALERT_LAYOUT_CHANGE, AlertLayoutChange::LayoutChanged::WIDTH)));
}

double ContainerBox::editor_get_width(Harmonia::Unit unit_type)
{
    if(unit_type == Harmonia::Unit::NOT_SET) return 0;
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

void ContainerBox::set_height(double length, Harmonia::Unit unit_type){
    ContainerBox::height.length = length;
    ContainerBox::height.unit_type = unit_type;
    alert_manager->dispatch_alert(memnew(AlertLayoutChange(ALERT_LAYOUT_CHANGE, AlertLayoutChange::LayoutChanged::HEIGHT)));
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

double ContainerBox::get_height(Harmonia::Unit unit_type){
    if(unit_type == Harmonia::Unit::NOT_SET) return 0;
    if(debug_outputs) UtilityFunctions::print("[RUNTIME] Width: ", width.length, " ", width.unit_type);

    Size2 window_size = get_tree()->get_root()->get_visible_rect().size;

    if(parent == nullptr){
        Size2 window_size = get_tree()->get_root()->get_visible_rect().size;
        return ContainerUnitConverter::get_height(height, window_size.y, window_size, unit_type);
    }

    return ContainerUnitConverter::get_height(height, parent->get_height(), window_size, unit_type);
}

double ContainerBox::editor_get_height(Harmonia::Unit unit_type)
{    
    if(unit_type == Harmonia::Unit::NOT_SET) return 0;
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
    }else if(p_what == NOTIFICATION_RESIZED){
        // Process to convert new size to current unit size.
    }
}

void ContainerBox::_bind_methods(){
    BIND_ENUM_CONSTANT(Position::STATIC);
    BIND_ENUM_CONSTANT(Position::ABSOLUTE);
    BIND_ENUM_CONSTANT(Position::RELATIVE);

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

    ClassDB::bind_method(D_METHOD("set_position_type", "new_type"), &ContainerBox::set_position_type);
    ClassDB::bind_method(D_METHOD("get_position_type"), &ContainerBox::get_position_type);

    ClassDB::bind_method(D_METHOD("set_pos_x_str", "new_x"), &ContainerBox::set_pos_x_str);
    ClassDB::bind_method(D_METHOD("get_pos_x_str"), &ContainerBox::get_pos_x_str);
    ClassDB::bind_method(D_METHOD("set_pos_y_str", "new_y"), &ContainerBox::set_pos_y_str);
    ClassDB::bind_method(D_METHOD("get_pos_y_str"), &ContainerBox::get_pos_y_str);
    
    ClassDB::bind_method(D_METHOD("set_pos_x", "new_x", "unit_type"), &ContainerBox::set_pos_x);
    ClassDB::bind_method(D_METHOD("get_pos_x", "unit_type"), &ContainerBox::get_pos_x);
    ClassDB::bind_method(D_METHOD("set_pos_y", "new_y", "unit_type"), &ContainerBox::set_pos_y);
    ClassDB::bind_method(D_METHOD("get_pos_y", "unit_type"), &ContainerBox::get_pos_y);

    const String positioning_types = "STATIC:0,ABSOLUTE:1,RELATIVE:2";

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "alert_manager", PROPERTY_HINT_RESOURCE_TYPE, "alert_manager", PROPERTY_USAGE_NO_EDITOR), "set_alert_manager", "get_alert_manager");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "width_str", PROPERTY_HINT_TYPE_STRING, "width_str", PROPERTY_USAGE_NO_EDITOR), "set_width_str", "get_width_str");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "height_str", PROPERTY_HINT_TYPE_STRING, "height_str", PROPERTY_USAGE_NO_EDITOR), "set_height_str", "get_height_str");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "debug_outputs", PROPERTY_HINT_TYPE_STRING, "debug_outputs", PROPERTY_USAGE_NO_EDITOR), "set_debug_outputs", "get_debug_outputs");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "positioning", PROPERTY_HINT_ENUM, positioning_types, PROPERTY_USAGE_DEFAULT), "set_position_type", "get_position_type");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "pos_x_str", PROPERTY_HINT_TYPE_STRING, "pos_x_str", PROPERTY_USAGE_NO_EDITOR), "set_pos_x_str", "get_pos_x_str");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "pos_y_str", PROPERTY_HINT_TYPE_STRING, "pos_y_str", PROPERTY_USAGE_NO_EDITOR), "set_pos_y_str", "get_pos_y_str");
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
    }else if(name == "pos_x_str"){
        set_pos_x_str(p_value);
        return true;
    }else if(name == "pos_y_str"){
        set_pos_y_str(p_value);
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
    }else if(name == "pos_x_str"){
        r_ret = pos_x_str;
        return true;
    }else if(name == "pos_y_str"){
        r_ret = pos_y_str;
        return true;
    }
	return false;
}

void ContainerBox::_get_property_list(List<PropertyInfo> *p_list) const
{
    p_list->push_back(PropertyInfo(Variant::STRING, "width_str"));
    p_list->push_back(PropertyInfo(Variant::STRING, "height_str"));
    p_list->push_back(PropertyInfo(Variant::BOOL, "debug_outputs"));
    p_list->push_back(PropertyInfo(Variant::STRING, "pos_x_str"));
    p_list->push_back(PropertyInfo(Variant::STRING, "pos_y_str"));
}
