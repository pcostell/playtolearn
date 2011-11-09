
#pragma once

#include "frontend/display/Display.hpp"
#include "frontend/TextResponse.hpp"
#include "frontend/FreeResponseResponse.hpp"

#include "frontend/FreeResponseAnswerInteraction.hpp"
#include "frontend/TextAnswerInteraction.hpp"
#include "frontend/GenericInteraction.hpp"
#include "frontend/Interaction.hpp"

#include <string>


namespace PlayToLearn {
namespace Frontend {

class TextDisplay : public Display {
public:

  typedef boost::shared_ptr<TextDisplay> Ptr;
  typedef boost::shared_ptr<const TextDisplay> ConstPtr;

  void main_display_loop();

  //void draw_object(const Object & object);

private:
  void displayInteraction(InteractionResponse::Ptr response);
  Interaction::Ptr handleInteraction(InteractionResponse::Ptr response);

  void displayTextInteraction(TextResponse::Ptr response);
  TextAnswerInteraction::Ptr handleTextInteraction(TextResponse::Ptr response);

  void displayFreeResponseInteraction(FreeResponseResponse::Ptr response);
  FreeResponseAnswerInteraction::Ptr handleFreeResponseInteraction(FreeResponseResponse::Ptr response);

  InteractionResponse::Ptr current_response_;

  std::string GetLine();
};

} // namespace Frontend
} // namespace PlayToLearn
