
#pragma once

#include "../Display.hpp"
#include <string>

class TextDisplay : public Display {
public:
  void main_display_loop();

private:
  std::string GetLine();
};