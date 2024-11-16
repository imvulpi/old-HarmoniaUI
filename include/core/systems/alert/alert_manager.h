#pragma once

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include "core/systems/alert/alert.h"

using namespace godot;

class AlertManager : public Object
{
    GDCLASS(AlertManager, Object);
private:

public:
    AlertManager() = default;
    ~AlertManager() = default;
    
    std::unordered_map<std::string, std::unordered_set<std::shared_ptr<std::function<void(Alert*)>>>> binds;
    std::unordered_map<std::string, std::unordered_map<int64_t, std::shared_ptr<std::function<void(Alert*)>>>> godot_binds; // int64_t for Callable hash

    void dispatch_alert(Alert* alert);
    void add_bind(std::string alert_type, std::shared_ptr<std::function<void(Alert*)>> function);
    void remove_bind(std::string alert_type, std::shared_ptr<std::function<void(Alert*)>> function);

    void godot_add_bind(String alert_type, Callable callable);
    void godot_remove_bind(String alert_type, Callable callable);

protected:
    static void _bind_methods();
};