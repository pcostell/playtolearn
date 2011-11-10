
#include <iostream>
#include <fstream>

#include <boost/scoped_ptr.hpp>

#include "frontend/InteractionResponses.hpp"
#include "frontend/display/Display.hpp"
#include "frontend/display/text/TextDisplay.hpp"
#include "frontend/display/graphics/IrrlichtDisplay.hpp"

#include "backend/Engine.hpp"
#include "backend/AttributeMap.hpp"

#include "util/Constants.hpp"

namespace PlayToLearn {
namespace Frontend {

//////////////////////
// Global variables //
//////////////////////

boost::scoped_ptr<Display> display(new Frontend::TextDisplay());
boost::scoped_ptr<Backend::Engine> backend(new Backend::Engine());

/////////////////////////
// Function prototypes //
/////////////////////////

void loadFrontendEngine();

////////////////////////
// Callback functions //
////////////////////////

InteractionResponse::Ptr interaction(Interaction::Ptr interaction) {
  /*
  Backend::AttributeMap m;
  m.set_value(Util::kTextAttribute, "HAHAHAHA");
  m.set_value(Util::kObjectIDAttribute, interaction->object_id().value());
  m.set_value(Util::kStateIDAttribute, 0);
  return InteractionResponse::Ptr(new TextResponse(m));
  */

  return backend->register_interaction(interaction);
}

void drawScene() {

}

void loadGame() {

}

//////////////////////
// Helper Functions //
//////////////////////

void loadFrontendEngine() {
  display->register_interaction_function(interaction);
  display->register_draw_scene_function(drawScene);
  display->register_load_game_function(loadGame);
  display->main_display_loop();
}

} // namespace Frontend
} // namespace PlayToLearn

///////////////////
// Main function //
///////////////////

int main(int argc, char **argv)
{
  //handleOSXPaths();
  PlayToLearn::Frontend::loadFrontendEngine();
  return 0;
}

