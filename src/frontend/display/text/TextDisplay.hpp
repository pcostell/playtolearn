
#pragma once

#include "../Display.hpp"
#include "../../../TextResponse.hpp"

#include <string>


namespace PlayToLearn {
namespace Frontend {

class TextDisplay : public Display {
public:
  void main_display_loop();

  //void draw_object(const Object & object);

private:
  void handleResponse(InteractionResponse::Ptr ir);
  void handleTextResponse(TextResponse::Ptr ir);

  std::string GetLine();
};

} // namespace Frontend
} // namespace PlayToLearn
