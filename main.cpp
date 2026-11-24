// Vaciar cola: despues de cada SwapBuffers, glFinish() espera a que la grafica termine el cuadro.
// Asi el driver no deja cuadros en cola y el siguiente cuadro empieza con lo ultimo que pulsaste.
// No cambia la logica ni la fisica del juego: solo espera a la grafica.

#include <Geode/Geode.hpp>
#include <Geode/modify/CCEGLView.hpp>

using namespace geode::prelude;

// Se lee al cargar y se actualiza al cambiar el ajuste: en cada cuadro solo se mira esta variable.
static bool s_enabled = false;

$on_mod(Loaded) {
	s_enabled = Mod::get()->getSettingValue<bool>("enabled");
	listenForSettingChanges<bool>("enabled", [](bool value) {
		s_enabled = value;
		log::info("Vaciar cola: {}", value ? "encendido" : "apagado");
	});
	log::info("Vaciar cola: {}", s_enabled ? "encendido" : "apagado");
}

class $modify(VaciarColaView, CCEGLView) {
	void swapBuffers() {
		CCEGLView::swapBuffers();
		if (s_enabled) {
			glFinish();
		}
	}
};
