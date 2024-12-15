#include "register_types.h"
#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "containers/container_box.h"
#include "containers/content_box.h"
#include "commons/unit_converter.h"
#include "core/systems/alert/alert.h"
#include "core/systems/alert/layout/alert_layout_change.h"
#include "core/systems/alert/alert_manager.h"

using namespace godot;

void initialize_harmonia(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_CLASS(Harmonia);
	GDREGISTER_VIRTUAL_CLASS(Alert);
	GDREGISTER_CLASS(AlertLayoutChange);
	GDREGISTER_CLASS(AlertManager);
	GDREGISTER_CLASS(ContentBox);
	GDREGISTER_CLASS(ContainerBox);
}

void deinitialize_harmonia(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
GDExtensionBool GDE_EXPORT harmonia_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_harmonia);
	init_obj.register_terminator(deinitialize_harmonia);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
