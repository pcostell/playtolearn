#include "TextDisplay.hpp"

#include <iostream>

using namespace PlayToLearn;
using namespace PlayToLearn::Frontend;
using namespace std;

void TextDisplay::main_display_loop() {

  cout << "Welcome to PlayToLearn" << endl;
  //InteractionResponse::Ptr ir(Interaction(0));
  //handleDisplayInteraction(ir);
  //LoadGame();
  InteractionResponse::Ptr ir(Interaction(0));
  displayInteraction(ir);

  while (current_response_) {
    /*Interaction::Ptr interaction = */handleInteraction(current_response_);
    //if(interaction) current_response_ = Interaction(interaction);
  }
}

//Interaction::ptr
void TextDisplay::handleInteraction(InteractionResponse::Ptr response) {
  switch (response->type()) {
    case InteractionResponse::IR_TEXT:
      //return
      handleTextInteraction(boost::static_pointer_cast<TextResponse>(response));
    //case InteractionResponse::IR_FREE_RESPONSE;
    //  return handleFreeResponseResponse(boost::static_pointer_cast<FreeResponseResponse>(ir));
    //case InteractionResponse::IR_MULTIPLE_CHOICE;
    //  return handleMultipleChoiceResponse(boost::static_pointer_cast<MultipleChoiceResponse>(ir));
  }
}

void TextDisplay::handleTextInteraction(TextResponse::Ptr response) {
  cout << response->text() << endl;
}
/*
void TextDisplay::handleFreeResponseResponse(FreeResponseResponse::Ptr response) {
  cout << response->text() << endl;
}

void TextDisplay::handleMultipleChoiceResponse(MultipleChoiceResponse::Ptr response) {

}
*/

void TextDisplay::displayInteraction(InteractionResponse::Ptr response) {
   switch (response->type()) {
    case InteractionResponse::IR_TEXT:
      displayTextInteraction(boost::static_pointer_cast<TextResponse>(response));
      break;
  // case InteractionResponse::IR_FREE_RESPONSE;
  //    handleFreeResponseResponse(boost::static_pointer_cast<FreeResponseResponse>(ir));
  //    break;
  //  case InteractionResponse::IR_MULTIPLE_CHOICE;
  //    handleMultipleChoiceResponse(boost::static_pointer_cast<MultipleChoiceResponse>(ir));
  //    break;
  }
}

void TextDisplay::displayTextInteraction(TextResponse::Ptr response) {
  cout << response->text() << endl;
}
/*
void TextDisplay::displayFreeResponseInteraction(FreeResponseResponse::Ptr response) {
  cout << response->text() << endl;
}

void TextDisplay::displayMultipleChoiceInteraction(MultipleChoiceResponse::Ptr response) {
  cout << response->text() << endl;
  for (size_t i = 0; i < response->answers.size(); ++i) {
    cout << ('A' + i) << " : " << response->answer[i] << endl;
  }
}*/


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
