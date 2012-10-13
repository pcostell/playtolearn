
#pragma once

#include <QColor>

#include "backend/AttributeMap.hpp"

namespace PlayToLearn {
namespace UI {

class TransitionNodePolicy {
public:
  enum ColorType {
    Default,
    Selected
  };

  virtual QColor color(ColorType type) const = 0;
  virtual std::string name() const = 0;
  virtual void transition_data(Backend::AttributeMap & attributes) const = 0;
  virtual std::string script(const Backend::TransitionFn & transition) const = 0;
};

}  /* namespace UI */
}  /* namespace PlayToLearn */