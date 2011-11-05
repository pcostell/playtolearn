
#include "TextDisplay.hpp"
#include "../../../Object.hpp"

#include <iostream>

using namespace PlayToLearn::Frontend;
using namespace std;

void TextDisplay::main_display_loop() {

  cout << "Welcome to PlayToLearn" << endl;
  while (true) {
    boost::shared_ptr<InteractionResponse> ir = Interaction(0);
    handleResponse(ir);
    DrawScene();
    cout << "> ";
    string line = GetLine();
    Interaction(0);
    cout << "You said: " << line << endl;
  }
}

void handleResponse(boost::shared_ptr<InteractionResponse> ir) {
  switch (ir->type()) {

  }
}

void TextDisplay::draw_object(const Object & object) {
  cout << object.get_description() << endl;
}

//////////////////////
// Helper functions //
//////////////////////

string TextDisplay::GetLine() {
  string line;
  getline(cin, line);
  return line;
}