/*
 * File: frontend/display/text/TextDisplay.cpp
 */

#include "frontend/display/text/TextDisplay.hpp"

#include <cctype>
#include <iostream>

#include <boost/make_shared.hpp>

#include "util/Constants.hpp"
#include "backend/Object.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** TextDisplay member functions, public */

void TextDisplay::main_display_loop() {
  // Display a generic welcome message:
  cout << "Welcome to PlayToLearn text adventure!" << endl;
  cout << "--------------------------------------" << endl;
  draw_scene();
  
  while (true) {
    // Pull the next interaction data and see if we should continue:
    InteractionPrompt::Ptr interaction_data = request_interaction(Util::kDefaultObject);
    if (!interaction_data) break;
    
    display_interaction_prompt(interaction_data);
    Interaction::Ptr interaction = handle_interaction(interaction_data);
    if (interaction) {
      string response = register_interaction(interaction);
      if (!response.empty())
        cout << response << endl;
    }
  }
}

/** TextDisplay member functions, private */

Interaction::Ptr TextDisplay::handle_interaction(InteractionPrompt::Ptr prompt) {
  switch (prompt->type()) {
    case InteractionPrompt::INTERACT_TEXT_PROMPT:
      return handle_text_interaction(boost::static_pointer_cast<TextPrompt>(prompt));
    case InteractionPrompt::INTERACT_FREE_RESPONSE_PROMPT:
      return handle_free_response_interaction(boost::static_pointer_cast<FreeResponsePrompt>(prompt));
    case InteractionPrompt::INTERACT_MULTIPLE_CHOICE_PROMPT:
      return handle_multiple_choice_interaction(boost::static_pointer_cast<MultipleChoicePrompt>(prompt));
  }
  
  return boost::shared_ptr<Frontend::Interaction>();
}

TextAnswer::Ptr TextDisplay::handle_text_interaction(TextPrompt::Ptr prompt) {
  return boost::make_shared<TextAnswer>(prompt->object_id());
}

FreeResponseAnswer::Ptr TextDisplay::handle_free_response_interaction(FreeResponsePrompt::Ptr prompt) {
  cout << "> ";
  return boost::make_shared<FreeResponseAnswer>(prompt->object_id(), prompt_user());
}

MultipleChoiceAnswer::Ptr TextDisplay::handle_multiple_choice_interaction(MultipleChoicePrompt::Ptr prompt) {
  while (true) {
    cout << "> ";
    string line = prompt_user();
    if (line.size() != 1) {
      cout << "Please choose a character." << endl;
    } else {
      char choice = toupper(line[0]);
      if ('A' <= choice && choice < 'A' + prompt->num_choices()) {
        return boost::make_shared<MultipleChoiceAnswer>(prompt->object_id(), choice - 'A');
      } else {
        cout << "Please choose one of the possible answers." << endl;
      }
    }
  }
}

void TextDisplay::display_interaction_prompt(InteractionPrompt::Ptr prompt) {
  switch (prompt->type()) {
    case InteractionPrompt::INTERACT_TEXT_PROMPT:
      display_text_prompt(boost::static_pointer_cast<TextPrompt>(prompt));
      break;
    case InteractionPrompt::INTERACT_FREE_RESPONSE_PROMPT:
      display_free_response_prompt(boost::static_pointer_cast<FreeResponsePrompt>(prompt));
      break;
    case InteractionPrompt::INTERACT_MULTIPLE_CHOICE_PROMPT:
      display_multiple_choice_prompt(boost::static_pointer_cast<MultipleChoicePrompt>(prompt));
      break;
  }
}

void TextDisplay::display_text_prompt(TextPrompt::Ptr prompt) {
  cout << prompt->text() << endl;
}

void TextDisplay::display_free_response_prompt(FreeResponsePrompt::Ptr prompt) {
  cout << prompt->text() << endl;
}

void TextDisplay::display_multiple_choice_prompt(MultipleChoicePrompt::Ptr prompt) {
  cout << prompt->text() << endl;
  for (int i = 0; i < prompt->num_choices(); ++i) {
    cout << '[' << static_cast<char>('A' + i) << "] " << prompt->choice(i) << endl;
  }
}

string TextDisplay::prompt_user() {
  string line;
  getline(cin, line);
  return line;
}

} // namespace Frontend
} // namespace PlayToLearn
