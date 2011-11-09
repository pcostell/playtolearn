
#pragma once

#include "frontend/InteractionResponse.hpp"
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
  void register_interaction_function(InteractionResponse::Ptr (*fn)(int id));
  void register_load_game_function(void (*fn)());

protected:
  void DrawScene();
  boost::shared_ptr<InteractionResponse> Interaction(int id);
  void LoadGame();

private:
  void (*drawScene_)();
  void (*loadGame_)();
  InteractionResponse::Ptr (*interact_)(int);
};

} // namespace Frontend
} // namespace PlayToLearn
