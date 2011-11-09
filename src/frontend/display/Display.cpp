
#include "frontend/display/Display.hpp"

using namespace PlayToLearn::Frontend;

///////////////////////////////////
// Display::Error public methods //
///////////////////////////////////

Display::Error::Error(const std::string & what) : std::runtime_error(what) {}

////////////////////////////
// Display public methods //
////////////////////////////

void Display::register_draw_scene_function(void (*fn)()) {
  drawScene_ = fn;
}

void Display::register_interaction_function(InteractionResponse::Ptr (*fn)(int id)) {
  interact_ = fn;
}

void Display::register_load_game_function(void (*fn)()) {
  loadGame_ = fn;
}

///////////////////////////////
// Display protected methods //
///////////////////////////////

void Display::DrawScene() {
  drawScene_();
}

PlayToLearn::InteractionResponse::Ptr Display::Interaction(int id) {
  return interact_(id);
}

void Display::LoadGame() {
  loadGame_();
}