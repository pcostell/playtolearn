/*
 * File: util/ErrorTypes.cpp
 */

#include "util/ErrorTypes.hpp"
#include <sstream>

using namespace std;

namespace PlayToLearn {
namespace Util {

/////////////////////////////////////////////////////////
// MissingAttributeError member implementation details //
/////////////////////////////////////////////////////////

/** public */

MissingAttributeError::MissingAttributeError(const string& attribute) :
  runtime_error(form_error_message(attribute))
{
  // empty body
}

/** private */

string MissingAttributeError::form_error_message(const string& attribute) const {
  stringstream err_ss;
  err_ss << "Requested attribute not in map: " << attribute;
  return err_ss.str();
}

/////////////////////////////////////////////////////
// InvalidStateError member implementation details //
/////////////////////////////////////////////////////

/** public */

InvalidStateError::InvalidStateError(int state_id) :
  runtime_error(form_error_message(state_id))
{
  // empty body
}

/** private */

string InvalidStateError::form_error_message(int state_id) const {
  stringstream err_ss;
  err_ss << "Invalid state ID requested: " << state_id;
  return err_ss.str();
}

////////////////////////////////////////////////////////////
// InvalidTransitionFnError member implementation details //
////////////////////////////////////////////////////////////

/** public */

InvalidTransitionFnError::InvalidTransitionFnError(int transition_fn_id) :
  runtime_error(form_error_message(transition_fn_id))
{
  // empty body
}

/** private */

string InvalidTransitionFnError::form_error_message(int transition_fn_id) const {
  stringstream err_ss;
  err_ss << "Invalid transition function ID requested: " << transition_fn_id;
  return err_ss.str();
}

//////////////////////////////////////////////////////////
// InvalidStateIndexError member implementation details //
//////////////////////////////////////////////////////////

/** public */

InvalidStateIndexError::InvalidStateIndexError(int transition_fn_id, int state_index) :
  runtime_error(form_error_message(transition_fn_id, state_index))
{
  // empty body
}

/** private */

string InvalidStateIndexError::form_error_message(int transition_fn_id, int state_index) const {
  stringstream err_ss;
  err_ss << "State index out of bounds for transition " << transition_fn_id << ": " << state_index;
  return err_ss.str();
}

//////////////////////////////////////////////////////
// MissingScriptError member implementation details //
//////////////////////////////////////////////////////

/** public */

MissingScriptError::MissingScriptError(int transition_fn_id) :
  runtime_error(form_error_message(transition_fn_id))
{
  // empty body
}

/** private */

string MissingScriptError::form_error_message(int transition_fn_id) const {
  stringstream err_ss;
  err_ss << "Missing external script for transition function: " << transition_fn_id;
  return err_ss.str();
}

////////////////////////////////////////////////////////
// PythonExecutionError member implementation details //
////////////////////////////////////////////////////////

/** public */

PythonExecutionError::PythonExecutionError(const string& what_arg) :
  runtime_error(what_arg)
{
  // empty body
}

} // namespace Util
} // namespace PlayToLearn
