#pragma once

#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/control.hpp>
#include "commons/container_unit_converter.h"
#include "core/systems/alert/alert_manager.h"

using namespace godot;

/// @brief Container class for all HarmoniaUI containers
class ContainerBox : public Control
{
    GDCLASS(ContainerBox, Control);

public:
    ContainerBox() = default;
    ~ContainerBox() = default;
    // Constants:
    const String ALERT_LAYOUT_CHANGE = "layout-change";

    double update_time = 0;
    double update_interval = 1.0;
    void ContainerBox::_ready();
    void ContainerBox::_process(double delta);
    void ContainerBox::_gui_input(const Ref<InputEvent> &p_gui_input);

    /// @brief Updates the container presentation/view in runtime
    void update_presentation();
    
    /// @brief [EDITOR] Updates the container presentation/view in editor
    void editor_update_presentation();
    
    AlertManager* alert_manager;
    AlertManager* get_alert_manager();
    void set_alert_manager(AlertManager* manager);

    ContainerBox* parent = nullptr;
    ContainerBox* get_parent_container();
    godot::List<ContainerBox*> children;

    /// @brief Should debug outputs be printed to the console?
    bool debug_outputs = false;
    
    /// @brief Sets debug outputs
    /// @param debug_outputs Should debug outputs be printed?
    void set_debug_outputs(bool debug_outputs);

    /// @brief Gets the debug outputs setting
    /// @return debug outputs option
    bool get_debug_outputs();

    LengthPair width; /* Width pair, stores length and unit */

    /// @brief Gets the width in provided unit
    /// @param unit_type Width unit type
    /// @return Width in the provided unit type
    double get_width(int unit_type = LengthUnit::PIXEL);

    /// @brief Sets the width to provided length and unit
    /// @param length Width length
    /// @param unit_type Width length unit type 
    void set_width(double length, int unit_type = LengthUnit::PIXEL);

    /// @brief An editor way of getting width, don't use runtime
    /// @param unit_type Width unit type
    /// @return Width in provided unit type
    double editor_get_width(int unit_type = LengthUnit::PIXEL);

    /// @brief Gets current width pair in a string representation
    /// @return Width string representation
    String get_width_str();

    /// @brief Sets width from a string representation of width length pair 
    /// @param length_and_unit string representataion of width length pair
    void set_width_str(String length_and_unit);
    String width_str; /* String representation of width */
    
    LengthPair height; /* Height pair, stores length and unit */

    /// @brief Gets the height in provided unit
    /// @param unit_type height unit type
    /// @return Height in the provided unit type
    double get_height(int unit_type = LengthUnit::PIXEL);

    /// @brief Sets the height to provided length and unit
    /// @param length Height length
    /// @param unit_type Height length unit type 
    void set_height(double length, int unit_type = LengthUnit::PIXEL);

    /// @brief An editor way of getting height, don't use runtime
    /// @param unit_type Height unit type
    /// @return Height in provided unit type
    double editor_get_height(int unit_type = LengthUnit::PIXEL);
    
    /// @brief Gets current height pair in a string representation
    /// @return Height string representation
    String get_height_str();

    /// @brief Sets height from a string representation of height length pair 
    /// @param length_and_unit string representataion of height length pair
    void set_height_str(String length_and_unit);
    String height_str; /* String representation of height */
protected:
    static void _bind_methods();
	bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;
    void _get_property_list(List<PropertyInfo> *p_list) const;
    void _notification(int p_what);
};
