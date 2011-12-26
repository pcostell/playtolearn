
#pragma once

#include "backend/AttributeMap.hpp"
#include "backend/TransitionFn.hpp"
#include "ui/TransitionNodePolicy.hpp"
#include "util/Constants.hpp"

namespace PlayToLearn {
namespace UI {

class FreeResponseTransitionNodePolicy : public TransitionNodePolicy {
public:

  virtual QColor color(ColorType type) const {
    switch (type) {
      case Default:
        return QColor(255, 0, 0);
      case Selected:
        return QColor(255, 100, 100);
    }
    return QColor(0, 0, 0);
  }

  virtual std::string name() const {
    return "Free Response Question";
  }

  virtual void transition_data(Backend::AttributeMap& attributes) const {
    attributes.set_value(Util::kInteractionPromptTypeAttribute, Util::kFreeResponsePromptTypeValue);
    attributes.set_value(Util::kStateIDAttribute, -1);
    attributes.set_value(Util::kObjectIDAttribute, -2);
    attributes.set_value(Util::kTextAttribute, "Question text");
  }

  virtual std::string script(const Backend::TransitionFn & transition) const {
    std::stringstream script_ss;
    script_ss << "def state_transition_";
    script_ss << transition.id();
    script_ss << "(am, gs):\n";
    script_ss << "\tif am['free_response_answer'] == 'red':\n";
    script_ss << "\t\tgs['response_text'] = 'Correct! You chose red!'\n";
    script_ss << "\t\treturn 0\n";
    script_ss << "\telse:\n";
    script_ss << "\t\tgs['response_text'] = 'Wrong color!'\n";
    script_ss << "\t\treturn 1\n";
    return script_ss.str();
  }

};

}  /* namespace UI */
}  /* namespace PlayToLearn */