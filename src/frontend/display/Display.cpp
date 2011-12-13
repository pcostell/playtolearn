
#include "frontend/display/Display.hpp"

namespace PlayToLearn {
namespace Frontend {

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

void Display::register_interaction_function(InteractionResponse::Ptr (*fn)(Interaction::Ptr)) {
  interact_ = fn;
}

///////////////////////////////
// Display protected methods //
///////////////////////////////

void Display::draw_scene() {
  drawScene_();
}

InteractionResponse::Ptr Display::interact(Interaction::Ptr interaction) {
  return interact_(interaction);
}

} // namespace Frontend
} // namespace PlayToLearn
