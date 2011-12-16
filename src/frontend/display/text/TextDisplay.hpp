/*
 * File: frontend/display/text/TextDisplay.hpp
 */

#pragma once

#include <string>

#include "frontend/Interactions.hpp"
#include "frontend/InteractionPrompts.hpp"
#include "frontend/display/Display.hpp"

namespace PlayToLearn {
namespace Frontend {

// The TextDisplay class represents the concrete display module which provides
// a text-only game for the user to play.
class TextDisplay : public Display {
public:
  // The Ptr typedef allows us to refer to shared_ptr<TextDisplay> smart
  // pointers as TextDisplay::Ptr. A const version is provided as well.
  typedef boost::shared_ptr<TextDisplay> Ptr;
  typedef boost::shared_ptr<const TextDisplay> ConstPtr;
  
  // See the related comment in the Display.hpp file.
  void main_display_loop();
  
  //void draw_object(const Object & object);

private:
  // member functions
  
  void display_interaction_prompt(InteractionPrompt::Ptr prompt);
  Interaction::Ptr handle_interaction(InteractionPrompt::Ptr prompt);

  void display_text_prompt(TextPrompt::Ptr prompt);
  TextAnswer::Ptr handle_text_interaction(TextPrompt::Ptr prompt);

  void display_free_response_prompt(FreeResponsePrompt::Ptr prompt);
  FreeResponseAnswer::Ptr handle_free_response_interaction(FreeResponsePrompt::Ptr prompt);

  void display_multiple_choice_prompt(MultipleChoicePrompt::Ptr prompt);
  MultipleChoiceAnswer::Ptr handle_multiple_choice_interaction(MultipleChoicePrompt::Ptr prompt);

  std::string prompt_user();
};

} // namespace Frontend
} // namespace PlayToLearn
