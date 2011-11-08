
#pragma once

#include "../Display.hpp"
#include "../../../TextResponse.hpp"

#include <string>


namespace PlayToLearn {
namespace Frontend {

class TextDisplay : public Display {
public:

  typedef boost::shared_ptr<TextDisplay> Ptr;
  typedef boost::shared_ptr<const TextDisplay> ConstPtr;

  void main_display_loop();

  void handle_text_response(TextResponse::Ptr response);
  void handle_free_response_response(FreeResponseResponse::Ptr response);
  void handle_multiple_choice_response(MultipleChoiceResponse::Ptr response);


  //void draw_object(const Object & object);

private:
  InteractionResponse::Ptr current_response_;

  std::string GetLine();
};

} // namespace Frontend
} // namespace PlayToLearn
