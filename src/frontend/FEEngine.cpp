
#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

#include <iostream>
#include <fstream>
#include <functional>

#include <boost/scoped_ptr.hpp>

#include "frontend/InteractionResponse.hpp"
#include "frontend/display/Display.hpp"
#include "frontend/display/text/TextDisplay.hpp"
#include "frontend/display/graphics/IrrlichtDisplay.hpp"

#include "backend/Engine.hpp"
#include "backend/AttributeMap.hpp"
#include "frontend/TextResponse.hpp"

namespace PlayToLearn {
namespace Frontend {

//////////////////////
// Global variables //
//////////////////////

boost::scoped_ptr<Display> display;
boost::scoped_ptr<Backend::Engine> backend;

/////////////////////////
// Function prototypes //
/////////////////////////

void handleOSXPaths();

////////////////////////
// Callback functions //
////////////////////////

InteractionResponse::Ptr interaction(int id) {
  Backend::AttributeMap m;
  m.set_value("text", "HAHAHAHA");
  InteractionResponse::Ptr ir = InteractionResponse::Ptr(new TextResponse(m));
}

void drawScene() {

}

void loadGame() {

}

//////////////////////
// Helper Functions //
//////////////////////

void loadFrontendEngine() {
  display = boost::scoped_ptr<Display>(new Frontend::TextDisplay());
  backend = boost::scoped_ptr<Backend::Engine>(new Backend::Engine());

  display->register_interaction_function(interaction);
  display->register_draw_scene_function(drawScene);
  display->register_load_game_function(loadGame);
  display->main_display_loop();
}

/*
 * This function ensures that relative paths in OSX operate from the bundle's
 * resource directory.
 */
void handleOSXPaths() {
  #ifdef __APPLE__
  CFBundleRef mainBundle = CFBundleGetMainBundle();
  CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
  char path[PATH_MAX];
  if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
  {
      exit(-1);
  }
  CFRelease(resourcesURL);

  chdir(path);
  #endif
}

} // namespace Frontend
} // namespace PlayToLearn

///////////////////
// Main function //
///////////////////

void initializeLogging() {
  boost::logging::core::get()->set_filter
  (
    flt::attr< logging::trivial::severity_level >("Severity") >= boost::logging::trivial::info
  )
}

int main(int argc, char **argv)
{
  //handleOSXPaths();
  loadFrontendEngine();
  return 0;
}

