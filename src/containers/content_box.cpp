#include "containers/content_box.h"
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/v_scroll_bar.hpp>
#include <godot_cpp/classes/engine.hpp>

void ContentBox::apply_overflowing(){
    if(is_overflowed_y || is_overflowed_x){
        if(overflowing_behaviour == Harmonia::OverflowBehaviour::HIDDEN){
            set_clip_contents(true);
        }else if(overflowing_behaviour == Harmonia::OverflowBehaviour::SCROLL){
            set_clip_contents(true);
        }else if(overflowing_behaviour == Harmonia::OverflowBehaviour::VISIBLE){
            set_clip_contents(false);
        }
    }
}

void ContentBox::apply_scrolling(double step_x, double step_y){
    if(step_y < 0 && scroll_top_px == -max_scroll_top_px) return;
    else if(step_y > 0 && scroll_top_px == min_scroll_top_px) return;

    if(step_x < 0 && scroll_left_px == -max_scroll_left_px) return;
    else if(step_x > 0 && scroll_left_px == min_scroll_left_px) return;

    TypedArray<Node> children = get_children();
    if(step_y < 0 && scroll_top_px - step_y < -max_scroll_top_px){
        step_y = fabs(max_scroll_top_px + scroll_top_px);
    }else if(step_y > 0 && scroll_top_px + step_y > min_scroll_top_px){
        step_y = min_scroll_top_px - (scroll_top_px + step_y);
    }

    if(step_x < 0 && scroll_left_px - step_x < -max_scroll_left_px){
        step_x = fabs(max_scroll_left_px + scroll_left_px);
    }else if(step_x > 0 && scroll_left_px + step_x > min_scroll_left_px){
        step_x = min_scroll_left_px - (scroll_left_px + step_x);
    }

    set_scroll_top_px(scroll_top_px+step_y);
    set_scroll_left_px(scroll_left_px+step_x);

    for (size_t i = 0; i < children.size(); i++)
    {
        if(auto* child = Object::cast_to<Control>(children[i])){
            Vector2 child_position = child->get_position();
            
            if(is_overflowed_y){
                child_position.y += step_y;
                child->set_position(Vector2(child_position.x, child_position.y));
            }

            if(is_overflowed_x){
                child->set_position(Vector2(child_position.x + step_x, child_position.y));
            }
        }
    } 
}

void ContentBox::set_scroll_top_px(double value){
    scroll_top_px = value;
    if(scrollbar_y){
        scrollbar_y->set_max(max_scroll_top_px);
        scrollbar_y->set_min(min_scroll_top_px);
        scrollbar_y->set_value(fabs(scroll_top_px));
    }
}

void ContentBox::set_scroll_left_px(double value){
    scroll_left_px = value;
    if(scrollbar_x){
        scrollbar_x->set_max(max_scroll_left_px);
        scrollbar_x->set_min(min_scroll_left_px);
        scrollbar_x->set_value(fabs(scroll_left_px));
    }
}

void ContentBox::check_overflowing(){
    Vector2 size = get_size();
    TypedArray<Node> children = get_children();

    double max_overflow_x {0};
    double max_overflow_y {0};
    double sum_child_size_x {0};
    double sum_child_size_y {0};

    for (size_t i = 0; i < children.size(); i++)
    {
        if(auto* child = Object::cast_to<Control>(children[i])){
            Vector2 child_position = child->get_position();
            Vector2 child_size = child->get_size();
            sum_child_size_x += child_size.x;
            sum_child_size_y += child_size.y;
        }
    }

    if(sum_child_size_x > size.x){
        is_overflowed_x = true;
        overflowing_size_x_px = sum_child_size_x - size.x;
    }

    if(sum_child_size_y > size.y){
        is_overflowed_y = true;
        overflowing_size_y_px = sum_child_size_y - size.y;
    }

    min_scroll_top_px = 0;
    max_scroll_top_px = overflowing_size_y_px;
    min_scroll_left_px = 0;
    max_scroll_left_px = overflowing_size_x_px;
}

bool ContentBox::calculate_y_priority(){
    if(is_overflowed_y == false){
        return false;
    }
    if(is_overflowed_x){
        double scroll_check = get_size().y * scroll_x_checking_size;
        Vector2 mouse_pos = get_global_mouse_position();
        Vector2 scroll_size = scrollbar_x->get_size();
        Vector2 scroll_position = scrollbar_x->get_global_position();

        // top: pos_y - check | mousepos.y >= top
        // left: pos_x | mousepos.x >= left
        // right: size_x + pos_x | mousepos.x <= right
        // down: size_y + pos_y | mousepox.y <= down

        if(mouse_pos.y >= scroll_position.y - scroll_check &&
           mouse_pos.y <= scroll_size.y + scroll_position.y &&
           mouse_pos.x >= scroll_position.x &&
           mouse_pos.x <= scroll_size.x + scroll_position.x)
        {
            return false;
        }
    }
    return true;
}

double ContentBox::calculate_overflowing(double child_pos, double child_size, double parent_size){
    double child_sum = child_pos + child_size;
    if(child_sum > parent_size){
        return child_sum-parent_size;
    }
    return 0;
}

void ContentBox::_gui_input(const Ref<InputEvent> &p_gui_input){
    if(overflowing_behaviour == Harmonia::OverflowBehaviour::SCROLL && (is_overflowed_x || is_overflowed_y)){
        if(auto* mouse_event = Object::cast_to<InputEventMouseButton>(*p_gui_input)){
            if(mouse_event->is_pressed()){
                if(mouse_event->get_button_index() == MouseButton::MOUSE_BUTTON_WHEEL_UP){
                    bool y_priority = calculate_y_priority();
                    if(y_priority){
                        apply_scrolling(0, scroll_step_top_px);
                    }else{
                        apply_scrolling(scroll_step_left_px, 0);            
                    }   
                }else if(mouse_event->get_button_index() == MouseButton::MOUSE_BUTTON_WHEEL_DOWN){
                    bool y_priority = calculate_y_priority();
                    if(y_priority){
                        apply_scrolling(0, -scroll_step_top_px);
                    }else{
                        apply_scrolling(-scroll_step_left_px, 0);
                    }
                }
            }
        }
    }
}

void ContentBox::_bind_methods(){
    
}
bool ContentBox::_set(const StringName &p_name, const Variant &p_value){
    return false;
}
bool ContentBox::_get(const StringName &p_name, Variant &r_ret) const {
    return false;
}
void ContentBox::_get_property_list(List<PropertyInfo> *p_list) const {
    
}

void ContentBox::_notification(int p_what){
    
}