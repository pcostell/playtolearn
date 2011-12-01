/*
 * File: backend/State.cpp
 */

#include "util/ErrorTypes.hpp"
#include "backend/State.hpp"

using namespace std;

namespace PlayToLearn {
namespace Backend {

/////////////////////////////////////////
// State member implementation details //
/////////////////////////////////////////

/** public */

State::State(ID id) : id_(id) {
  // empty body
}

TransitionFn::ID State::transition_fn_id(Object::ID object_id) const {
  map<Object::ID, TransitionFn::ID>::const_iterator itr = object_ids_.find(object_id);
  if (itr == object_ids_.end())
    throw Util::InvalidObjectError(id_.value(), object_id.value());
  
  return object_ids_.find(object_id)->second;
}

void State::insert_object(Object::ID object_id, TransitionFn::ID fn_id) {
  object_ids_[object_id] = fn_id;
}

void State::remove_object(Object::ID id) {
  object_ids_.erase(id);
}

} // namespace Backend
} // namespace PlayToLearn
