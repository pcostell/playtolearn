
#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

#include <iostream>
#include <fstream>
#include <functional>

#include "frontend/InteractionResponse.hpp"
#include "display/Display.hpp"
#include "display/text/TextDisplay.hpp"
#include "display/graphics/IrrlichtDisplay.hpp"

#include "backend/Engine.hpp"
#include "backend/AttributeMap.hpp"
#include "frontend/TextResponse.hpp"

using namespace PlayToLearn;

Frontend::Display * display;
Backend::Engine * backend;

InteractionResponse::Ptr interaction(int id) {
  Backend::AttributeMap m;
  m.set_value("text", "HAHAHAHA");
  InteractionResponse::Ptr ir = InteractionResponse::Ptr(new TextResponse(m));
}

void drawScene() {

}

void loadGame() {

}

void handleOSXPaths();

int main(int argc, char **argv)
{
  //handleOSXPaths();

  display = new Frontend::TextDisplay();
  backend = new Backend::Engine();

  display->register_interaction_function(interaction);
  display->register_draw_scene_function(drawScene);
  display->register_load_game_function(loadGame);
  display->main_display_loop();

  delete display;

  return 0;
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
