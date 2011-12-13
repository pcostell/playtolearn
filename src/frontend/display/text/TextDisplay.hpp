/*
 * File: frontend/display/text/TextDisplay.hpp
 */

#pragma once

#include <string>

#include "frontend/Interactions.hpp"
#include "frontend/InteractionResponses.hpp"
#include "frontend/display/Display.hpp"

namespace PlayToLearn {
namespace Frontend {

class TextDisplay : public Display {
public:
  // The Ptr typedef allows us to refer to shared_ptr<TextDisplay> smart
  // pointers as TextDisplay::Ptr. A const version is provided as well.
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

  void displayMultipleChoiceInteraction(MultipleChoiceResponse::Ptr response);
  MultipleChoiceAnswerInteraction::Ptr handleMultipleChoiceInteraction(MultipleChoiceResponse::Ptr response);

  InteractionResponse::Ptr current_response_;

  std::string GetLine();
};

} // namespace Frontend
} // namespace PlayToLearn
