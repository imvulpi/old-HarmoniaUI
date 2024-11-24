#include <godot_cpp/core/class_db.hpp>
#include "core/systems/alert/alert.h"

/// @brief Work In Progress. This class will allow you to bind to a layout change alert in a alert system.
class AlertLayoutChange : public Alert
{
public:
    enum LayoutChanged {
        WIDTH,
        HEIGHT,
        POSITION
        // ... Other will be added
    };

    AlertLayoutChange() = default;
    AlertLayoutChange(String name, LayoutChanged changed);
    
    LayoutChanged layout_changed;
    String get_alert_name() const;
protected:
    void _bind_methods();
};

inline String AlertLayoutChange::get_alert_name() const
{
    return String(alert_name);
}

VARIANT_ENUM_CAST(AlertLayoutChange::LayoutChanged);