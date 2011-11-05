
#include "TextDisplay.hpp"

#include <iostream>

using namespace PlayToLearn::Frontend;
using namespace std;

void TextDisplay::main_display_loop() {

  cout << "Welcome to PlayToLearn" << endl;
  Interaction(0);
  /*
  while (true) {
    DrawScene();
    cout << "> ";
    string line = GetLine();
    Interaction(0);
    cout << "You said: " << line << endl;
  }*/
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
