
#pragma once

#include "../Display.hpp"

#include <irrlicht.h>


class IrrlichtDisplay : public Display {
public:
  IrrlichtDisplay();
  ~IrrlichtDisplay();
  void main_display_loop();

private:
  irr::video::IVideoDriver* driver;
  irr::scene::ISceneManager* smgr;
  irr::gui::IGUIEnvironment* guienv;
  irr::IrrlichtDevice * device;
};