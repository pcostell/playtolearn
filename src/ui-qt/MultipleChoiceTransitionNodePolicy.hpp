
#pragma once

#include "ui/TransitionNodePolicy.hpp"

namespace PlayToLearn {
namespace UI {

class MultipleChoiceTransitionNodePolicy : public TransitionNodePolicy {
public:

  virtual QColor color(ColorType type) const {
    switch (type) {
      case Default:
        return QColor(0, 255, 0);
      case Selected:
        return QColor(100, 255, 100);
    }
    return QColor(0, 0, 0);
  }

  virtual std::string name() const {
    return "Multiple Choice Question";
  }

  virtual void transition_data(Backend::AttributeMap& attributes) const {
    attributes.set_value(Util::kInteractionPromptTypeAttribute, Util::kMultipleChoicePromptTypeValue);
    attributes.set_value(Util::kTextAttribute, "How fat is Patrick?");
    attributes.set_value(Util::kNumMCChoicesAttribute, 2);
    attributes.set_value(Util::kMCChoiceAttribute + "0", "fat");
    attributes.set_value(Util::kMCChoiceAttribute + "1", "extremely fat");
  }

  virtual std::string script(const Backend::TransitionFn & transition) const {
    std::stringstream ss;
    ss << "def " << Util::kTransitionFnScriptFunctionName << transition.id() << "(am, gs):\n"
       << "  if am['" << Util::kMCAnswerIndexAttribute << "'] == '0':\n"
       << "    gs['" << Util::kInteractionResponseText << "'] = 'Not fat enough!'\n"
       << "  else:\n"
       << "    gs['" << Util::kInteractionResponseText << "'] = 'Correct again!'\n"
       << "  return 0\n";
    return ss.str();
  }


};

}  /* namespace UI */
}  /* namespace PlayToLearn */