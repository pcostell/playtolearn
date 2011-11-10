
#pragma once

#include "frontend/InteractionResponses.hpp"
#include "frontend/Interactions.hpp"

#include <functional>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

namespace PlayToLearn {
namespace Frontend {

class Display {
public:

  typedef boost::shared_ptr<Display> Ptr;
  typedef boost::shared_ptr<const Display> ConstPtr;

  class Error : public std::runtime_error {
  public:
    explicit Error (const std::string& what);
  };

  virtual ~Display() {};
  virtual void main_display_loop() {};

  virtual void display_dialog() {};
  //virtual void draw_object(const Object & npc) {};

  void register_draw_scene_function(void (*fn)());
  void register_interaction_function(InteractionResponse::Ptr (*fn)(Interaction::Ptr response));

protected:
  void DrawScene();
  InteractionResponse::Ptr Interaction(Interaction::Ptr interaction);
  void LoadGame();

private:
  void (*drawScene_)();
  InteractionResponse::Ptr (*interact_)(Interaction::Ptr);
};

} // namespace Frontend
} // namespace PlayToLearn
