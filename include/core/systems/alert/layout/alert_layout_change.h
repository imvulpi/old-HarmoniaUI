#include <godot_cpp/core/class_db.hpp>
#include "core/systems/alert/alert.h"

/// @brief Class which allows for binding for size, position, or margin layout changes
class AlertLayoutChange : public Alert
{
    GDCLASS(AlertLayoutChange, Alert);
public:
    enum LayoutChanged {
        UNSPECIFIED,
        WIDTH,
        HEIGHT,
        POSITION,
        MARGIN,
        PADDING,
    };

    AlertLayoutChange() = default;
    AlertLayoutChange(String name, LayoutChanged changed);
    
    /// @brief The specific layout that was changed.
    LayoutChanged layout_changed {LayoutChanged::UNSPECIFIED};
    /// @brief Gets this alerts name 
    String get_alert_name() const;
protected:
    static void _bind_methods();
};

inline String AlertLayoutChange::get_alert_name() const
{
    return String(alert_name);
}

VARIANT_ENUM_CAST(AlertLayoutChange::LayoutChanged);