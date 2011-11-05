
#include "Display.hpp"

using namespace PlayToLearn::Frontend;

///////////////////////////////////
// Display::Error public methods //
///////////////////////////////////

Display::Error::Error(const std::string & what) : std::runtime_error(what) {}

////////////////////////////
// Display public methods //
////////////////////////////

void Display::register_draw_scene_function(void (*fn)()) {
  _drawScene = fn;
}

void Display::register_interaction_function(InteractionResponse::Ptr (*fn)(int id)) {
  _interact = fn;
}

///////////////////////////////
// Display protected methods //
///////////////////////////////

void Display::DrawScene() {
  _drawScene();
}

PlayToLearn::InteractionResponse::Ptr Display::Interaction(int id) {
  return _interact(id);
}
