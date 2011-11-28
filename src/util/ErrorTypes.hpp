/*
 * File: util/ErrorTypes.hpp
 */

#pragma once

#include <stdexcept>
#include <string>

// IMPORTANT: when adding new exception types, do NOT include any other headers
// from this project. This file is used by enough modules that it would almost
// certainly cause a circular include dependency.

namespace PlayToLearn {
namespace Util {

//////////////////////////////
// AttributeMap error types //
//////////////////////////////

/**
 * The MissingAttributeError class represents the exception thrown when a
 * query is made to the AttributeMap for an attribute which doesn't exist.
 */
class MissingAttributeError : public std::runtime_error {
public:
  /**
   * The MissingAttributeError constructor creates the error object with the
   * missing attribute specified.
   */
  explicit MissingAttributeError(const std::string& attribute);

private:
  //////////////////////
  // member functions //
  //////////////////////
  
  std::string form_error_message(const std::string& attribute) const;
};

//////////////////////////////
// StateMachine error types //
//////////////////////////////

/**
 * The InvalidStateError class represents the exception thrown when a query is
 * made to the state machine for a state whose ID doesn't exist.
 */
class InvalidStateError : public std::runtime_error {
public:
  /**
   * The InvalidStateError constructor creates the error object with the invalid
   * state ID specified.
   */
  explicit InvalidStateError(int state_id);

private:
  //////////////////////
  // member functions //
  //////////////////////
  
  std::string form_error_message(int state_id) const;
};

/**
 * The InvalidTransitionFnError class represents the exception thrown when a
 * query is made to the state machine for a transition function whose ID doesn't
 * exist.
 */
class InvalidTransitionFnError : public std::runtime_error {
public:
  /**
   * The InvalidTransitionFnError constructor creates the error object with the
   * invalid transition function ID specified.
   */
  explicit InvalidTransitionFnError(int transition_fn_id);

private:
  //////////////////////
  // member functions //
  //////////////////////
  
  std::string form_error_message(int transition_fn_id) const;
};

//////////////////////////////
// TransitionFn error types //
//////////////////////////////

/**
 * The InvalidStateIndexError class represents the exception thrown when a query
 * is made to a transition function for a state index that is out of bounds.
 */
class InvalidStateIndexError : public std::runtime_error {
public:
  /**
   * The InvalidStateIndexError constructor creates the error object with the
   * invalid state index and transition function ID specified.
   */
  InvalidStateIndexError(int transition_fn_id, int state_index);

private:
  //////////////////////
  // member functions //
  //////////////////////
  
  std::string form_error_message(int transition_fn_id, int state_index) const;
};

/**
 * The MissingScriptError class represents the exception thrown when a state
 * transition is requested on a TransitionFn object which hasn't yet been
 * assigned a corresponding ExternalTransitionFn object.
 */
class MissingScriptError : public std::runtime_error {
public:
  /**
   * The MissingScriptError constructor creates the error object with the
   * transition function ID specified.
   */
  MissingScriptError(int transition_fn_id);

private:
  //////////////////////
  // member functions //
  //////////////////////
  
  std::string form_error_message(int transition_fn_id) const;
};

////////////////////////////////////
// PythonTransitionFn error types //
////////////////////////////////////

/**
 * The PythonExecutionError class represents the type of exception thrown when
 * an error occurs in the execution of a Python script.
 */
class PythonExecutionError : public std::runtime_error {
public:
  /**
   * The PythonExecutionError contructor creates the error object with the
   * specified description string.
   */
  explicit PythonExecutionError(const std::string& what_arg);
};

} // namespace Util
} // namespace PlayToLearn
