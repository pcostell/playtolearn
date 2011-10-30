
#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

#include <iostream>
#include <fstream>

#include "display/Display.hpp"
#include "display/text/TextDisplay.hpp"

/*
This is the main method. We can now use main() on every platform.
*/
int main(int argc, char **argv)
{
  // ----------------------------------------------------------------------------
// This makes relative paths work in C++ for OS X by changing directory to the Resources folder inside the .app bundle
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
    {
        // error!
    }
    CFRelease(resourcesURL);

    chdir(path);
#endif

  Display * d = new TextDisplay();

  d->main_display_loop();

  delete d;

  return 0;
}