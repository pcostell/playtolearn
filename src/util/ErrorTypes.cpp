/*
 * File: util/ErrorTypes.cpp
 */

#include "util/ErrorTypes.hpp"

using namespace std;

namespace PlayToLearn {
namespace Util {

/////////////////////////////////////////////////////////
// MissingAttributeError member implementation details //
/////////////////////////////////////////////////////////

/** public */

MissingAttributeError::MissingAttributeError(const string& what_arg) :
  runtime_error(what_arg)
{
  // empty body
}

/////////////////////////////////////////////////////
// InvalidStateError member implementation details //
/////////////////////////////////////////////////////

/** public */

InvalidStateError::InvalidStateError(const string& what_arg, int id) :
  runtime_error(what_arg), state_id_(id)
{
  // empty body
}

////////////////////////////////////////////////////////////
// InvalidTransitionFnError member implementation details //
////////////////////////////////////////////////////////////

/** public */

InvalidTransitionFnError::InvalidTransitionFnError(const string& what_arg, int id) :
  runtime_error(what_arg), transition_fn_id_(id)
{
  // empty body
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
