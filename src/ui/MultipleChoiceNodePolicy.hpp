
#pragma once

#include "ui/NodePolicy.hpp"

namespace PlayToLearn {
namespace UI {

class MultipleChoiceNodePolicy : public NodePolicy {
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

  }

  virtual std::string script(const Backend::TransitionFn & transition) const {
    return "";
  }


};

}  /* namespace UI */
}  /* namespace PlayToLearn */