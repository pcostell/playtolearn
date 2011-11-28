/*
 * File: backend/TransitionFn.cpp
 */

#include "backend/TransitionFn.hpp"
#include "backend/State.hpp"
#include "backend/external/PythonTransitionFn.hpp"
#include "util/ErrorTypes.hpp"
#include <stdexcept>
#include <sstream>

using namespace std;

namespace PlayToLearn {
namespace Backend {

////////////////////////////////////////////////
// TransitionFn member implementation details //
////////////////////////////////////////////////

/** public */

TransitionFn::TransitionFn(ID id) : id_(id) {
  // empty body
}

State::ID TransitionFn::state_at(int index) const {
  check_state_index(index);
  return state_ids_[index];
}

void TransitionFn::add_state(State::ID state_id) {
  state_ids_.push_back(state_id);
}

void TransitionFn::remove_state(int index) {
  check_state_index(index);
  state_ids_.erase(state_ids_.begin() + index);
}

void TransitionFn::set_python_function(const string& python_code, const string& function_name) {
  script_fn_.reset(new PythonTransitionFn(python_code));
  function_name_ = function_name;
}

State::ID TransitionFn::next_state(const AttributeMap& interaction, AttributeMap& global_state) const {
  if (!script_fn_)
    throw Util::MissingScriptError(id_.value());
  
  return state_at(script_fn_->execute(function_name_, interaction, global_state));
}

/** private */

/*
 * check_state_index checks that the specified index is within valid bounds. If
 * it isn't, the member function throws a InvalidStateIndexError exception.
 */
void TransitionFn::check_state_index(int index) const {
  if (index < 0 || index >= num_states())
    throw Util::InvalidStateIndexError(id_.value(), index);
}

} // namespace Backend
} // namespace PlayToLearn
