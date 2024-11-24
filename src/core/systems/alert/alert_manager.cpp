#include "core/systems/alert/alert_manager.h"
#include "godot_cpp/variant/utility_functions.hpp"
// std::function to godot equalivemt.

void AlertManager::dispatch_alert(Alert* alert){
    if(alert == nullptr){
        return;
    }

    auto ascii_str = alert->get_alert_name().ascii();
    const char* alert_name = ascii_str.ptr();
    std::string alert_name_str(alert_name);
    std::unordered_set<std::shared_ptr<std::function<void(Alert*)>>> bind_functions = binds[alert_name_str];
    for (std::shared_ptr<std::function<void(Alert*)>> func : bind_functions)
    {
        (*func)(alert);
    }
}

void AlertManager::add_bind(std::string alert_type, std::shared_ptr<std::function<void(Alert*)>> function){
    binds[alert_type].insert(function);
}

void AlertManager::remove_bind(std::string alert_type, std::shared_ptr<std::function<void(Alert*)>> function){
    binds[alert_type].erase(function);
}

void AlertManager::godot_add_bind(String alert_type, Callable callable){
    const char* alert_type_char = alert_type.ascii().ptr();
    std::function<void(Alert*)> func = [callable](Alert* alert){
        callable.call(alert);
    };

    auto shared_func = std::make_shared<std::function<void(Alert*)>>(func);
    godot_binds[alert_type_char][callable.hash()] = shared_func;
    binds[alert_type_char].insert(shared_func);
}

// To be tested
void AlertManager::godot_remove_bind(String alert_type, Callable callable){
    const char* alert_type_char = alert_type.ascii().ptr();
    std::shared_ptr<std::function<void(Alert*)>> shared_func = godot_binds[alert_type_char][callable.hash()];
    binds[alert_type_char].erase(shared_func);
    godot_binds[alert_type_char].erase(callable.hash());
}

void AlertManager::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("dispatch_alert", "alert"), &AlertManager::dispatch_alert);
    ClassDB::bind_method(D_METHOD("add_bind", "alert_type", "function"), &AlertManager::godot_add_bind);
    ClassDB::bind_method(D_METHOD("remove_bind", "alert_type", "fuction"), &AlertManager::godot_remove_bind);
}
