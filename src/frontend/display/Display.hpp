
#pragma once

#include <functional>
#include <stdexcept>
#include <string>

//#include "../../Object.hpp"


namespace PlayToLearn {
namespace Frontend {

class Display {
public:
  class Error : public std::runtime_error {
  public:
    explicit Error (const std::string& what) : std::runtime_error(what) {}
  };

  virtual ~Display() {};
  virtual void main_display_loop() {};

  virtual void display_dialog() {};
  //virtual void draw_object(const Object & npc) {};


  void register_draw_scene_function(void (*fn)()) { _drawScene = fn;}
  void register_interaction_function(void (*fn)(int id)) { _interact = fn;}

protected:
  void DrawScene() { _drawScene(); }
  void Interaction(int id) { _interact(id); }

private:
  void (*_drawScene)();
  void (*_interact)(int);
};

} // namespace Frontend
} // namespace PlayToLearn
