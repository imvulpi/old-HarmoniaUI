#include "core/systems/alert/layout/alert_layout_change.h"

AlertLayoutChange::AlertLayoutChange(String name, LayoutChanged changed)
{
    alert_name = name;
    layout_changed = changed;
}

void AlertLayoutChange::_bind_methods()
{
    BIND_ENUM_CONSTANT(AlertLayoutChange::WIDTH);
    BIND_ENUM_CONSTANT(AlertLayoutChange::HEIGHT);
    BIND_ENUM_CONSTANT(AlertLayoutChange::POSITION);
    BIND_ENUM_CONSTANT(AlertLayoutChange::MARGIN);
    BIND_ENUM_CONSTANT(AlertLayoutChange::PADDING);
}