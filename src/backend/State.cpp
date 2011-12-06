/*
 * File: backend/State.cpp
 */

#include "backend/State.hpp"

#include "util/ErrorTypes.hpp"
#include "backend/Object.hpp"
#include "backend/TransitionFn.hpp"

using namespace std;

namespace PlayToLearn {
namespace Backend {

/** State member functions, public */

State::State(ID id) : id_(id) {
  // empty body
}

bool State::contains_object(Object::ID id) const {
  return object_ids_.count(id);
}

TransitionFn::ID State::transition_fn_id(Object::ID object_id) const {
  map<Object::ID, TransitionFn::ID>::const_iterator itr = object_ids_.find(object_id);
  if (itr == object_ids_.end())
    throw Util::InvalidObjectError(id_, object_id);
  
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
