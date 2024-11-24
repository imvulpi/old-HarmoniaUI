#pragma once

#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include "commons/container_unit_converter.h"
#include "core/systems/alert/alert_manager.h"
#include "core/harmonia.h"

using namespace godot;

/// @brief Container class for all HarmoniaUI containers
class ContainerBox : public Control
{
    GDCLASS(ContainerBox, Control);
public:
    ContainerBox() = default;
    ~ContainerBox() = default;
    
    // Constants:
    
    /// @brief Alert of layout change, that being position, width, height or other layout change
    const String ALERT_LAYOUT_CHANGE = "layout-change";

    /// @brief Enum used for positioning of containers.
    enum Position { 
        STATIC,   // Normal
        ABSOLUTE, // Positioned to parent
        RELATIVE, // Positioned from the original location
    };

    /// @brief Update time from the last update
    /// @note This will get removed in the future.
    double update_time = 0;

    /// @brief The interval of updates 
    /// @note This will get removed in the future.
    double update_interval = 1.0;

    void ContainerBox::_ready();
    void ContainerBox::_process(double delta);
    void ContainerBox::_gui_input(const Ref<InputEvent> &p_gui_input);

    /// @brief Updates the container presentation/view in runtime
    void update_presentation();
    /// @brief Updates the container children positions in runtime
    void update_children_position(TypedArray<Node> children);
    
    /// @brief [EDITOR] Updates the container presentation/view in editor
    void editor_update_presentation();
    /// @brief [EDITOR] Updates the container children positions in editor
    void editor_update_children_position(TypedArray<Node> children);
    
    /// @brief Alert manager of this containers. Bind to this manager if you want to react to this containers alerts
    AlertManager* alert_manager = memnew(AlertManager);
    AlertManager* get_alert_manager();
    void set_alert_manager(AlertManager* manager);

    /// @brief ContainerBox parent of this container, only ContainerBox classes are set.
    ContainerBox* parent = nullptr;

    /// @brief gets containerBox parent of this container if one exists.
    /// @return ContainerBox parent or nullptr
    ContainerBox* get_parent_container();
    
    /// @brief The type of positioning of this containers children. Default STATIC.
    Position position_type = Position::STATIC;

    /// @brief Sets a positioning type for this containers children.
    void set_position_type(Position new_type);
    /// @brief Returns the positioning type for this containers children
    Position get_position_type();
    
    /// BELOW Str pos are positions set in the editor or in the code using getter/setter
    /// They string posistions get processed to create a pos_x length pair. Ex of str pos: 10%, 10px

    /// @brief X Position of this container.
    LengthPair pos_x;

    /// @brief X position setter in harmonia units.
    void set_pos_x(double new_x, Harmonia::Unit unit_type = Harmonia::Unit::PIXEL);

    /// @brief Retrieves X position in a provided unit.
    /// @param unit_type The unit type you want x pos to be returned in.
    double get_pos_x(Harmonia::Unit unit_type = Harmonia::Unit::PIXEL);

    /// @brief Editor way of retrieving X position
    /// @param unit_type The unit type you want x pos to be returned in.
    double editor_get_pos_x(Harmonia::Unit unit_type = Harmonia::Unit::PIXEL);

    /// @brief String posistion that gets processed to create a pos_x length pair when set by setter method.
    String pos_x_str;

    /// @brief Setter for string position X in harmonia units.
    void set_pos_x_str(String new_x);

    /// @brief Getter for string position X, includes harmonia unit.
    /// @note return ex: '100px', '100%', '100vw', '100vh'
    String get_pos_x_str();

    /// @brief Y Position of this container.
    LengthPair pos_y;

    /// @brief Y position setter in harmonia units.
    void set_pos_y(double new_y, Harmonia::Unit unit_type = Harmonia::Unit::PIXEL);

    /// @brief Retrieves Y position in a provided unit.
    /// @param unit_type The unit type you want y pos to be returned in.
    double get_pos_y(Harmonia::Unit unit_type = Harmonia::Unit::PIXEL);

    /// @brief Editor way of retrieving Y position
    /// @param unit_type The unit type you want y pos to be returned in.
    double editor_get_pos_y(Harmonia::Unit unit_type = Harmonia::Unit::PIXEL);

    /// @brief String posistion that gets processed to create a pos_y length pair when set by setter method.
    String pos_y_str;

    /// @brief Setter for string position X in harmonia units.
    void set_pos_y_str(String new_y);

    /// @brief Getter for string position X, includes harmonia unit.
    /// @note return ex: '100px', '100%', '100vw', '100vh'
    String get_pos_y_str();
    
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
    double get_width(Harmonia::Unit unit_type = Harmonia::Unit::PIXEL);

    /// @brief Sets the width to provided length and unit
    /// @param length Width length
    /// @param unit_type Width length unit type 
    void set_width(double length, Harmonia::Unit unit_type = Harmonia::Unit::PIXEL);

    /// @brief An editor way of getting width, don't use runtime
    /// @param unit_type Width unit type
    /// @return Width in provided unit type
    double editor_get_width(Harmonia::Unit unit_type = Harmonia::Unit::PIXEL);

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
    double get_height(Harmonia::Unit unit_type = Harmonia::Unit::PIXEL);

    /// @brief Sets the height to provided length and unit
    /// @param length Height length
    /// @param unit_type Height length unit type 
    void set_height(double length, Harmonia::Unit unit_type = Harmonia::Unit::PIXEL);

    /// @brief An editor way of getting height, don't use runtime
    /// @param unit_type Height unit type
    /// @return Height in provided unit type
    double editor_get_height(Harmonia::Unit unit_type = Harmonia::Unit::PIXEL);
    
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

VARIANT_ENUM_CAST(ContainerBox::Position);