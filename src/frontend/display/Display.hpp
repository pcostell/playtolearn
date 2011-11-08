
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

  virtual void handle_text_response(TextResponse::Ptr response) {};
  virtual void handle_free_response_response(FreeResponseResponse::Ptr response) {}
  virtual void handle_multiple_choice_response(MultipleChoiceResponse::Ptr response) {}


  void register_draw_scene_function(void (*fn)());
  void register_interaction_function(InteractionResponse::Ptr (*fn)(int id));

protected:
  void DrawScene();
  boost::shared_ptr<InteractionResponse> Interaction(int id);

private:
  void (*_drawScene)();
  InteractionResponse::Ptr (*_interact)(int);
};

} // namespace Frontend
} // namespace PlayToLearn
