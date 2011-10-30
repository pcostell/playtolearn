
#include "TextDisplay.hpp"

#include <iostream>

using namespace std;

void TextDisplay::main_display_loop() {

  cout << "Welcome to EduGame" << endl;
  while (true) {
    string line = GetLine();
    cout << "You said: " << line << endl;
  }
}

//////////////////////
// Helper functions //
//////////////////////

string TextDisplay::GetLine() {
  string line;
  getline(cin, line);
  return line;
}