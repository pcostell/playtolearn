/*
 * File: util/ErrorTypes.cpp
 */

#include "util/ErrorTypes.hpp"

#include <sstream>

#include "backend/State.hpp"
#include "backend/Object.hpp"
#include "backend/TransitionFn.hpp"

using namespace std;

namespace PlayToLearn {
namespace Util {

/** MissingAttributeError member functions, public */

MissingAttributeError::MissingAttributeError(const string& attribute) :
  runtime_error(form_error_message(attribute))
{
  // empty body
}

/** MissingAttributeError member functions, private */

string MissingAttributeError::form_error_message(const string& attribute) const {
  stringstream err_ss;
  err_ss << "Requested attribute not in map: " << attribute;
  return err_ss.str();
}

/** InvalidStateError member functions, public */

InvalidStateError::InvalidStateError(Backend::State::ID id) :
  runtime_error(form_error_message(id))
{
  // empty body
}

/** InvalidStateError member functions, private */

string InvalidStateError::form_error_message(Backend::State::ID id) const {
  stringstream err_ss;
  err_ss << "Invalid state ID requested: " << id.value();
  return err_ss.str();
}

/** InvalidTransitionFnError member functions, public */

InvalidTransitionFnError::InvalidTransitionFnError(Backend::TransitionFn::ID id) :
  runtime_error(form_error_message(id))
{
  // empty body
}

/** InvalidTransitionFnError member functions, private */

string InvalidTransitionFnError::form_error_message(Backend::TransitionFn::ID id) const {
  stringstream err_ss;
  err_ss << "Invalid transition function ID requested: " << id.value();
  return err_ss.str();
}

/** InvalidObjectError member functions, public */

InvalidObjectError::InvalidObjectError(Backend::State::ID state_id, Backend::Object::ID object_id) :
  runtime_error(form_error_message(state_id, object_id))
{
  // empty body
}

/** InvalidObjectError member functions, private */

string InvalidObjectError::form_error_message(Backend::State::ID state_id, Backend::Object::ID object_id) const {
  stringstream err_ss;
  err_ss << "Invalid object ID requested for state " << state_id.value() << ": " << object_id.value();
  return err_ss.str();
}

/** InvalidStateIndexError member functions, public */

InvalidStateIndexError::InvalidStateIndexError(Backend::TransitionFn::ID transition_fn_id, int state_index) :
  runtime_error(form_error_message(transition_fn_id, state_index))
{
  // empty body
}

/** InvalidStateIndexError member functions, private */

string InvalidStateIndexError::form_error_message(Backend::TransitionFn::ID transition_fn_id, int state_index) const {
  stringstream err_ss;
  err_ss << "State index out of bounds for transition " << transition_fn_id.value() << ": " << state_index;
  return err_ss.str();
}

/** MissingTransitionFnScriptError member functions, public */

MissingTransitionFnScriptError::MissingTransitionFnScriptError(Backend::TransitionFn::ID id) :
  runtime_error(form_error_message(id))
{
  // empty body
}

/** MissingTransitionFnScriptError member functions, private */

string MissingTransitionFnScriptError::form_error_message(Backend::TransitionFn::ID id) const {
  stringstream err_ss;
  err_ss << "Missing external script for transition function: " << id.value();
  return err_ss.str();
}

/** InvalidScriptTypeError member functions, public */

InvalidScriptTypeError::InvalidScriptTypeError(const string& script_type) :
  runtime_error(form_error_message(script_type))
{
  // empty body
}

/** InvalidScriptTypeError member functions, private */

string InvalidScriptTypeError::form_error_message(const string& script_type) const {
  stringstream err_ss;
  err_ss << "Unsupported script type: " << script_type;
  return err_ss.str();
}

/** MissingScriptError member functions, public */

MissingScriptError::MissingScriptError(const string& script_name) :
  runtime_error(form_error_message(script_name))
{
  // empty body
}

/** MissingScriptError member functions, private */

string MissingScriptError::form_error_message(const string& script_name) const {
  stringstream err_ss;
  err_ss << "Missing script: " << script_name;
  return err_ss.str();
}

/** PythonExecutionError member functions, public */

PythonExecutionError::PythonExecutionError(const string& what_arg) :
  runtime_error(what_arg)
{
  // empty body
}

} // namespace Util
} // namespace PlayToLearn
