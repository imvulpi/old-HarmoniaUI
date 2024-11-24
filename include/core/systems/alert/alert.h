#pragma once

#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

using namespace godot;

class Alert : public RefCounted
{
    GDCLASS(Alert, RefCounted);
public:
    Alert() = default;
    ~Alert() = default;
    Alert(String name);
     
    String alert_name = "";
    virtual void set_alert_name(String new_name);
    virtual String get_alert_name();
protected:
    static void _bind_methods();
    bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;
    void _get_property_list(List<PropertyInfo> *p_list) const;
};

inline Alert::Alert(String name) : alert_name(name)
{
    alert_name = name;
}