#include "core/systems/alert/alert.h"

void Alert::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_alert_name"), &Alert::get_alert_name);
    ClassDB::bind_method(D_METHOD("set_alert_name", "alert_name"), &Alert::set_alert_name);
}

void Alert::set_alert_name(String new_name) {
    alert_name = new_name;
}

String Alert::get_alert_name() {
    return alert_name;
}

bool Alert::_set(const StringName &p_name, const Variant &p_value){
    String name = p_name;
    if(name == "set_alert_name"){
        set_alert_name(p_value);
        return true;
    }
	return false;
}

bool Alert::_get(const StringName &p_name, Variant &r_ret) const {
    String name = p_name;
    if(name == "get_alert_name"){
        r_ret = alert_name;
        return true;
    }
    return false;
}

void Alert::_get_property_list(List<PropertyInfo> *p_list) const {
    p_list->push_back(PropertyInfo(Variant::STRING, "alert_name"));
}