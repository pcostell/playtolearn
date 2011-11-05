#include "TextDisplay.hpp"

#include <iostream>

using namespace PlayToLearn;
using namespace PlayToLearn::Frontend;
using namespace std;

void TextDisplay::main_display_loop() {

  cout << "Welcome to PlayToLearn" << endl;
  while (true) {
    boost::shared_ptr<InteractionResponse> ir(Interaction(0));
    handleResponse(ir);
    cout << "> ";
    string line = GetLine();
  }
}

void TextDisplay::handleResponse(InteractionResponse::Ptr ir) {
  switch (ir->type()) {
    case InteractionResponse::IR_TEXT:
      handleTextResponse(boost::static_pointer_cast<TextResponse>(ir));
      break;
  }
}

void TextDisplay::handleTextResponse(TextResponse::Ptr ir) {
  cout << ir->text() << endl;
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
