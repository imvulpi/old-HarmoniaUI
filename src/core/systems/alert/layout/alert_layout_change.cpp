#include "core/systems/alert/layout/alert_layout_change.h"

AlertLayoutChange::AlertLayoutChange(String name, LayoutChanged changed)
{
    alert_name = name;
    layout_changed = changed;
}