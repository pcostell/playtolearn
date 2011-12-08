/*
 * File: FEEngine.cpp
 */

#include <iostream>
#include <fstream>

#include <boost/scoped_ptr.hpp>

#include "util/Constants.hpp"
#include "backend/AttributeMap.hpp"
#include "backend/Engine.hpp"
#include "frontend/InteractionResponses.hpp"
#include "frontend/display/Display.hpp"
#include "frontend/display/text/TextDisplay.hpp"
#include "frontend/display/graphics/IrrlichtDisplay.hpp"

namespace PlayToLearn {
namespace Frontend {

/** global variables */

boost::scoped_ptr<Display> display;
boost::scoped_ptr<Backend::Engine> engine;

/** free function declarations */

void LoadFrontendEngine();

/** callback functions */

InteractionResponse::Ptr HandleInteraction(Interaction::Ptr interaction) {
  return engine->register_interaction(interaction);
}

void DrawScene() {
  // empty for text program
}

/** free functions, private */

void LoadFrontendEngine() {
  // Initialize the front end's variables:
  display.reset(new Frontend::TextDisplay());
  engine.reset(new Backend::Engine(0, Backend::State::ID(0)));
  
  display->register_interaction_function(HandleInteraction);
  display->register_draw_scene_function(DrawScene);
  display->main_display_loop();
}

} // namespace Frontend
} // namespace PlayToLearn

/** program entry point */

int main(int argc, char **argv) {
  //handleOSXPaths();
  PlayToLearn::Frontend::LoadFrontendEngine();
  return 0;
}
