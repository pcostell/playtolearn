/*
 * File: frontend/display/Display.hpp
 */
#pragma once

#include <stdexcept>
#include <string>
#include <functional>

#include <boost/shared_ptr.hpp>

#include "util/UniqueID.hpp"
#include "frontend/Interactions.hpp"
#include "frontend/InteractionResponses.hpp"

namespace PlayToLearn {

/** outside class declarations */

namespace Backend {
  class Object;
}

namespace Frontend {

/** class definitions */

class Display {
public:

  typedef boost::shared_ptr<Display> Ptr;
  typedef boost::shared_ptr<const Display> ConstPtr;

  class Error : public std::runtime_error {
  public:
    explicit Error(const std::string& what);
  };
  
  // The Display constructor initializes the internal callback functions of the
  // Display class to NULL.
  Display();
  
  // The Display destructor is declared pure virtual in order to ensure that the
  // Display class may be used polymorphically.
  virtual ~Display();
  
  // set_request_interaction_fn sets the function invoked when requesting data
  // associated with an interaction.
  void set_request_interaction_fn(InteractionResponse::Ptr (*fn)(Util::UniqueID<Backend::Object> id));
  
  // set_register_interaction_fn sets the function invoked when registering a
  // player interaction.
  void set_register_interaction_fn(void (*fn)(Interaction::Ptr response));
  
  // set_draw_scene_fn sets the function invoked when drawing a scene.
  void set_draw_scene_fn(void (*fn)());
  
  // main_display_loop is the code which should be repeatedly run by the
  // frontend engine in order to drive the game.
  virtual void main_display_loop() = 0;
  
  // TODO: why is this virtual with an empty body?
  virtual void display_dialog() {}
  
  //virtual void draw_object(const Object & npc) {}

protected:
  // member functions
  InteractionResponse::Ptr request_interaction(Util::UniqueID<Backend::Object> id);
  void register_interaction(Interaction::Ptr interaction);
  void draw_scene();
  void load_game();

private:
  // member variables
  InteractionResponse::Ptr (*request_interaction_fn_)(Util::UniqueID<Backend::Object> id);
  void (*register_interaction_fn_)(Interaction::Ptr);
  void (*draw_scene_fn_)();
};

} // namespace Frontend
} // namespace PlayToLearn
