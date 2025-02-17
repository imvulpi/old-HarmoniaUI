#pragma once

#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/v_scroll_bar.hpp>
#include <godot_cpp/classes/h_scroll_bar.hpp>
#include "core/harmonia.h"

using namespace godot;

/// @brief This is a container/box that is used inside ContainerBoxes to manage overflowing. It can manage scrolling and other while not disturbing or limiting the API of containerbox
/// ||| Be aware: This container doesn't manage positioning or any other stuff. ContainerBox should manage it through this box.
class ContentBox : public Control
{
    GDCLASS(ContentBox, Control);
public:
    ContentBox() = default;
    ~ContentBox() = default;
    
    Harmonia::OverflowBehaviour overflowing_behaviour {Harmonia::SCROLL};
    VScrollBar* scrollbar_y = nullptr;
    HScrollBar* scrollbar_x = nullptr;

    /// @brief Is the content box standalone of part of a containerbox. The positioning wont be applied if its NOT standalone to allow container positioning.
    bool standalone {true};
    
    /// @brief Step of scrolling in px UP or DOWN
    double scroll_step_top_px {10};
    double scroll_step_left_px {10};

    bool is_overflowed_y {false}; /*Is y axis overflowed*/
    bool is_overflowed_x {false}; /*Is x axis overflowed*/
    double overflowing_size_x_px {0}; /*Size of overflowing on x axis*/
    double overflowing_size_y_px {0}; /*Size of overflowing on y axis*/
    
    /// @brief Checking size in % around scollbar x, if scrolled in that area scrollx is used.
    double scroll_x_checking_size = {0.2};
    
    /// @brief Value of how much have containers been moved from top (increases on going down/decreases on going up)
    double scroll_top_px {0};
    /// @brief Sets scroll top px
    void set_scroll_top_px(double value);
    /// @brief The least value of moving containers up, this is where scrolling UP stops (usually 0)
    double min_scroll_top_px {0};
    /// @brief The max value of moving containers up, this is where scrolling DOWN stops (usually overflow size y)
    double max_scroll_top_px {0};
    
    /// @brief Value of how much have containers been moved from left
    double scroll_left_px {0};
    /// @brief Sets scroll left px
    void set_scroll_left_px(double value);
    /// @brief The least value of moving containers left, this is where scrolling LEFT stops (usually 0)
    double min_scroll_left_px {0};
    /// @brief The max value of moving containers left, this is where scrolling RIGHT stops (usually overflow size x)
    double max_scroll_left_px {0};

    /// @brief How much should all content be offsetted by? (when negative overflow) (can be used by container to offset it there)
    double offset_left_px {0};
    /// @brief How much should all content be offsetted by? (when negative overflow) (can be used by container to offset it there)
    double offset_top_px {0};

    /// @brief Applies scrolling by steps
    /// @param step_x The movement on x axis
    /// @param step_y The movement on y axis
    void apply_scrolling(double step_x, double step_y);
    /// @brief Applies overflowing rules like clipping, doesnt apply scrolling or check overflowing by default
    void apply_overflowing();
    /// @brief Checks overflowing, warning: for now simple check no container specific padding/margin pos etc.
    void check_overflowing();
    /// @brief Calculates whether y scrolling should have priority over x scrolling
    bool calculate_y_priority();
    /// @brief Calculates overflowing based on child_pos, child_size and parent size
    double calculate_overflowing(double child_pos, double child_size, double parent_size);

    void _gui_input(const Ref<InputEvent> &p_gui_input);
protected:
    static void _bind_methods();
	bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;
    void _get_property_list(List<PropertyInfo> *p_list) const;
    void _notification(int p_what);
};