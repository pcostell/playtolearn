
#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

#include <iostream>
#include <fstream>
#include <functional>

#include "display/Display.hpp"
#include "display/text/TextDisplay.hpp"

using namespace PlayToLearn;

Frontend::Display * display;

void interaction(int id) {
  std::cout << "BLAH" << std::endl;
}

void drawScene() {

}

void handleOSXPaths();

int main(int argc, char **argv)
{
  #ifdef __APPLE__
  handleOSXPaths();
  #endif

  display = new Frontend::TextDisplay();

  display->register_interaction_function(interaction);
  display->register_draw_scene_function(drawScene);
  display->main_display_loop();

  delete display;

  return 0;
}

/*
 * This function ensures that relative paths in OSX operate from the bundle's
 * resource directory.
 */
void handleOSXPaths() {
  CFBundleRef mainBundle = CFBundleGetMainBundle();
  CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
  char path[PATH_MAX];
  if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
  {
      exit(-1);
  }
  CFRelease(resourcesURL);

  chdir(path);
}