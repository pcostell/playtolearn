

#pragma once

#include "ui/TransitionNodePolicy.hpp"

namespace PlayToLearn {
namespace UI {

class TextTransitionNodePolicy : public TransitionNodePolicy {
public:

  virtual QColor color(ColorType type) const {
    switch (type) {
      case Default:
        return QColor(0, 0, 255);
      case Selected:
        return QColor(100, 100, 255);
    }
    return QColor(0, 0, 0);
  }

  virtual std::string name() const {
    return "Text";
  }

  virtual void transition_data(Backend::AttributeMap& attributes) const {
    attributes.set_value(Util::kInteractionPromptTypeAttribute, Util::kMultipleChoicePromptTypeValue);
    attributes.set_value(Util::kStateIDAttribute, 3);
    attributes.set_value(Util::kObjectIDAttribute, -2);
    attributes.set_value(Util::kTextAttribute, "That is interesting.");
  }

  virtual std::string script(const Backend::TransitionFn & transition) const {
    std::stringstream ss;
    ss << "def " << Util::kTransitionFnScriptFunctionName << transition.id() << "(am, gs):\n"
       << "  return 0\n";
    return ss.str();
  }


};

}  /* namespace UI */
}  /* namespace PlayToLearn */