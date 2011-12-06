#include "frontend/display/text/TextDisplay.hpp"

#include <iostream>

#include "backend/Object.hpp"

using namespace PlayToLearn;
using namespace PlayToLearn::Frontend;
using namespace std;

void TextDisplay::main_display_loop() {

  cout << "Welcome to PlayToLearn" << endl;
  DrawScene();
  Interaction::Ptr it(new GenericInteraction(Backend::Object::ID(0)));
  current_response_ = Interaction(it);

  while (current_response_) {
    displayInteraction(current_response_);
    Interaction::Ptr interaction = handleInteraction(current_response_);
    if(interaction) current_response_ = Interaction(interaction);
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
  cout << response->text() << endl;
  string line = GetLine();
  return boost::shared_ptr<FreeResponseAnswerInteraction>(new FreeResponseAnswerInteraction(response->object_id(), line));
}

MultipleChoiceAnswerInteraction::Ptr TextDisplay::handleMultipleChoiceInteraction(MultipleChoiceResponse::Ptr response) {
  while(true) {
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
  for (size_t i = 0; i < response->num_choices(); ++i) {
    cout << ('A' + i) << " : " << response->choice(i) << endl;
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
