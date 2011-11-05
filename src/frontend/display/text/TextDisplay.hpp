
#pragma once

#include "../Display.hpp"
#include <string>

namespace PlayToLearn {
namespace Frontend {

class TextDisplay : public Display {
public:
  void main_display_loop();

  void draw_object(const Object & object);

private:
  void handleInteraction(boost::shared_ptr<InteractionResponse> ir);
  std::string GetLine();
};

} // namespace Frontend
} // namespace PlayToLearn