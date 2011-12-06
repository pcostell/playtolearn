/*
 * File: backend/TransitionFn.cpp
 */

#include "backend/TransitionFn.hpp"

#include <stdexcept>
#include <sstream>

#include "util/Constants.hpp"
#include "util/ErrorTypes.hpp"
#include "backend/AttributeMap.hpp"
#include "backend/State.hpp"
#include "backend/external/ExternalTransitionFn.hpp"
#include "backend/external/PythonTransitionFn.hpp"

using namespace std;

namespace PlayToLearn {
namespace Backend {

/** TransitionFn member functions, public */

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

void TransitionFn::set_python_function(const string& python_code) {
  script_fn_.reset(new PythonTransitionFn(python_code));
}

State::ID TransitionFn::next_state(const AttributeMap& interaction, AttributeMap& global_state) const {
  if (!script_fn_)
    throw Util::MissingTransitionFnScriptError(id_);
  
  return state_at(script_fn_->execute(Util::kTransitionFnScriptFunctionName, interaction, global_state));
}

/** TransitionFn member functions, private */

// check_state_index checks that the specified index is within valid bounds. If
// it isn't, the member function throws a InvalidStateIndexError exception.
void TransitionFn::check_state_index(int index) const {
  if (index < 0 || index >= num_states())
    throw Util::InvalidStateIndexError(id_, index);
}

} // namespace Backend
} // namespace PlayToLearn
