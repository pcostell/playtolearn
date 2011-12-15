/*
 * File: util/ErrorTypes.hpp
 */

#pragma once

#include <stdexcept>
#include <string>

#include "util/UniqueID.hpp"

// IMPORTANT: when adding new exception types, do NOT include any other headers
// from this project. This file is used by enough modules that it would almost
// certainly cause a circular include dependency. The exception is UniqueID.hpp,
// which does not require the use of any errors.

namespace PlayToLearn {

/** outside class declarations */

namespace Backend {
  class State;
  class Object;
  class TransitionFn;
}

namespace Util {

/** AttributeMap error class definitions */

// The MissingAttributeError class represents the exception thrown when a
// query is made to the AttributeMap for an attribute which doesn't exist.
class MissingAttributeError : public std::runtime_error {
public:
  // The MissingAttributeError constructor creates the error object with the
  // missing attribute specified.
  explicit MissingAttributeError(const std::string& attribute);

private:
  // member functions
  std::string form_error_message(const std::string& attribute) const;
};

/** StateMachine error class definitions */

// The InvalidStateError class represents the exception thrown when a query is
// made to the state machine for a state whose ID doesn't exist.
class InvalidStateError : public std::runtime_error {
public:
  // The InvalidStateError constructor creates the error object with the invalid
  // state ID specified.
  explicit InvalidStateError(UniqueID<Backend::State> id);

private:
  // member functions
  std::string form_error_message(UniqueID<Backend::State> id) const;
};

// The InvalidTransitionFnError class represents the exception thrown when a
// query is made to the state machine for a transition function whose ID doesn't
// exist.
class InvalidTransitionFnError : public std::runtime_error {
public:
  // The InvalidTransitionFnError constructor creates the error object with the
  // invalid transition function ID specified.
  explicit InvalidTransitionFnError(UniqueID<Backend::TransitionFn> id);

private:
  // member functions
  std::string form_error_message(UniqueID<Backend::TransitionFn> id) const;
};

/** State error class definitions */

// The InvalidObjectError class represents the exception thrown when a query is
// made to a State object for an object ID which doesn't exist for that state.
class InvalidObjectError : public std::runtime_error {
public:
  // The InvalidObjectError constructor creates the error object with the state
  // ID and invalid object ID specified.
  InvalidObjectError(UniqueID<Backend::State> state_id, UniqueID<Backend::Object> object_id);

private:
  // member functions
  std::string form_error_message(UniqueID<Backend::State> state_id, UniqueID<Backend::Object> object_id) const;
};

/** TransitionFn error class definitions */

// The InvalidStateIndexError class represents the exception thrown when a query
// is made to a transition function for a state index that is out of bounds.
class InvalidStateIndexError : public std::runtime_error {
public:
  // The InvalidStateIndexError constructor creates the error object with the
  // invalid state index and transition function ID specified.
  InvalidStateIndexError(UniqueID<Backend::TransitionFn> transition_fn_id, int state_index);

private:
  // member functions
  std::string form_error_message(UniqueID<Backend::TransitionFn> transition_fn_id, int state_index) const;
};

// The MissingTransitionFnScriptError class represents the exception thrown when
// a state transition is requested on a TransitionFn object which hasn't yet
// been assigned a corresponding ExternalTransitionFn object.
class MissingTransitionFnScriptError : public std::runtime_error {
public:
  // The MissingTransitionFnScriptError constructor creates the error object
  // with the transition function ID specified.
  MissingTransitionFnScriptError(UniqueID<Backend::TransitionFn> id);

private:
  // member functions
  std::string form_error_message(UniqueID<Backend::TransitionFn> id) const;
};

/** scripting error class definitions */

// The InvalidScriptTypeError class represents the type of exception thrown when
// a script of an unsupported type is encountered when loading game data.
class InvalidScriptTypeError : public std::runtime_error {
public:
  // The InvalidScriptTypeError constructor creates the error object with the
  // specified invalid script extension.
  explicit InvalidScriptTypeError(const std::string& script_type);

private:
  // member functions
  std::string form_error_message(const std::string& script_type) const;
};

// The MissingScriptError class represents the type of exception thrown when a
// script is missing from the data section of the game.
class MissingScriptError : public std::runtime_error {
public:
  // The MissingScriptError constructor creates the error object with the
  // specified script path name.
  explicit MissingScriptError(const std::string& script_name);

private:
  // member functions
  std::string form_error_message(const std::string& script_name) const;
};

/** Python error class definitions */

// The PythonExecutionError class represents the type of exception thrown when
// an error occurs in the execution of a Python script.
class PythonExecutionError : public std::runtime_error {
public:
  // The PythonExecutionError contructor creates the error object with the
  // specified description string.
  explicit PythonExecutionError(const std::string& what_arg);
};

/** InteractionPrompt error class definitions */

// The InvalidInteractionPromptTypeError class represents the type of exception
// thrown when an interaction prompt type which doesn't exist is requested.
class InvalidInteractionPromptTypeError : public std::runtime_error {
public:
  // The InvalidInteractionPromptTypeError constructor creates the error object
  // with the specified invlaid prompt type.
  explicit InvalidInteractionPromptTypeError(const std::string& prompt_type);

private:
  // member functions
  std::string form_error_message(const std::string& prompt_type) const;
};

} // namespace Util
} // namespace PlayToLearn
