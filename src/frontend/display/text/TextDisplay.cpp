/*
 * File: frontend/display/text/TextDisplay.cpp
 */

#include "frontend/display/text/TextDisplay.hpp"

#include <iostream>

#include "util/Constants.hpp"
#include "backend/Object.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

void TextDisplay::main_display_loop() {
  // Display a generic welcome message:
  cout << "Welcome to PlayToLearn text adventure!" << endl;
  cout << "--------------------------------------" << endl;
  draw_scene();
  
  while (true) {
    // Pull the next interaction data and see if we should continue:
    InteractionResponse::Ptr interaction_data = request_interaction(Util::kDefaultObject);
    if (!interaction_data) break;
    
    displayInteraction(interaction_data);
    Interaction::Ptr interaction = handleInteraction(interaction_data);
    if (interaction)
      register_interaction(interaction);
  }
}

Interaction::Ptr TextDisplay::handleInteraction(InteractionResponse::Ptr response) {
  switch (response->type()) {
    case InteractionResponse::IR_TEXT:
      return handleTextInteraction(boost::static_pointer_cast<TextResponse>(response));
    case InteractionResponse::IR_FREE_RESPONSE:
      return handleFreeResponseInteraction(boost::static_pointer_cast<FreeResponseResponse>(response));
    case InteractionResponse::IR_MULTIPLE_CHOICE:
      return handleMultipleChoiceInteraction(boost::static_pointer_cast<MultipleChoiceResponse>(response));
  }
  
  return boost::shared_ptr<Frontend::Interaction>();
}

TextAnswerInteraction::Ptr TextDisplay::handleTextInteraction(TextResponse::Ptr response) {
  return boost::shared_ptr<TextAnswerInteraction>(new TextAnswerInteraction(response->object_id()));
}

FreeResponseAnswerInteraction::Ptr TextDisplay::handleFreeResponseInteraction(FreeResponseResponse::Ptr response) {
  string line = GetLine();
  return boost::shared_ptr<FreeResponseAnswerInteraction>(new FreeResponseAnswerInteraction(response->object_id(), line));
}

MultipleChoiceAnswerInteraction::Ptr TextDisplay::handleMultipleChoiceInteraction(MultipleChoiceResponse::Ptr response) {
  while (true) {
    string line = GetLine();
    if (line.length() != 1) {
      cout << "Please choose a character." << endl;
    } else if (line[0] < 'A' || line[0] > 'A' + response->num_choices()) {
      cout << "Please choose one of the possible answers." << endl;
    } else {
      return boost::shared_ptr<MultipleChoiceAnswerInteraction>(new MultipleChoiceAnswerInteraction(response->object_id(), line[0] - 'A'));
    }
  }
}

void TextDisplay::displayInteraction(InteractionResponse::Ptr response) {
  switch (response->type()) {
    case InteractionResponse::IR_TEXT:
      displayTextInteraction(boost::static_pointer_cast<TextResponse>(response));
      break;
    case InteractionResponse::IR_FREE_RESPONSE:
      displayFreeResponseInteraction(boost::static_pointer_cast<FreeResponseResponse>(response));
      break;
    case InteractionResponse::IR_MULTIPLE_CHOICE:
      displayMultipleChoiceInteraction(boost::static_pointer_cast<MultipleChoiceResponse>(response));
      break;
  }
}

void TextDisplay::displayTextInteraction(TextResponse::Ptr response) {
  cout << response->text() << endl;
}

void TextDisplay::displayFreeResponseInteraction(FreeResponseResponse::Ptr response) {
  cout << response->text() << endl;
}

void TextDisplay::displayMultipleChoiceInteraction(MultipleChoiceResponse::Ptr response) {
  cout << response->text() << endl;
  for (int i = 0; i < response->num_choices(); ++i) {
    cout << ('A' + i) << ": " << response->choice(i) << endl;
  }
}


//void TextDisplay::draw_object(const Object & object) {
//  cout << object.get_description() << endl;
//}

//////////////////////
// Helper functions //
//////////////////////

string TextDisplay::GetLine() {
  string line;
  getline(cin, line);
  return line;
}

} // namespace Frontend
} // namespace PlayToLearn
