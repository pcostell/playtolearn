
#pragma once

#include <functional>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>
#include "../../InteractionResponse.hpp"

//#include "../../Object.hpp"


namespace PlayToLearn {
namespace Frontend {

class Display {
public:
  class Error : public std::runtime_error {
  public:
    explicit Error (const std::string& what);
  };

  virtual ~Display() {};
  virtual void main_display_loop() {};

  virtual void display_dialog() {};
  //virtual void draw_object(const Object & npc) {};


  void register_draw_scene_function(void (*fn)());
  void register_interaction_function(boost::shared_ptr<InteractionResponse> (*fn)(int id));

protected:
  void DrawScene();
  boost::shared_ptr<InteractionResponse> Interaction(int id);

private:
  void (*_drawScene)();
  void (*_interact)(int);
};

} // namespace Frontend
} // namespace PlayToLearn
