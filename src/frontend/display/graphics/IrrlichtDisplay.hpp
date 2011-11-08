
#pragma once

#include "../Display.hpp"

#include <irrlicht.h>

namespace PlayToLearn {
namespace Frontend {

class IrrlichtDisplay : public Display {
public:

  typedef boost::shared_ptr<IrrlichtDisplay> Ptr;
  typedef boost::shared_ptr<const IrrlichtDisplay> ConstPtr;

  IrrlichtDisplay();
  ~IrrlichtDisplay();
  void main_display_loop();

private:
  irr::video::IVideoDriver* driver;
  irr::scene::ISceneManager* smgr;
  irr::gui::IGUIEnvironment* guienv;
  irr::IrrlichtDevice * device;
};

} // namespace Frontend
} // namespace PlayToLearn