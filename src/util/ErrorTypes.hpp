/*
 * File: util/ErrorTypes.hpp
 */

#pragma once

#include "backend/State.hpp"
#include "backend/TransitionFn.hpp"
#include <stdexcept>
#include <string>

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
   * specified description string.
   */
  explicit MissingAttributeError(const std::string& what_arg);
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
   * The InvalidStateError constructor creates the error object with the
   * specified description string.
   */
  InvalidStateError(const std::string& what_arg, Backend::State::ID id);
  
  /**
   * state_id returns the ID of the state which caused the exception to be
   * thrown.
   */
  Backend::State::ID state_id() const;

private:
  //////////////////////
  // member variables //
  //////////////////////
  
  Backend::State::ID state_id_;
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
   * specified description string.
   */
  InvalidTransitionFnError(const std::string& what_arg, Backend::TransitionFn::ID id);
  
  /**
   * transition_fn_id returns the ID of the transition function which caused the
   * exception to be thrown.
   */
  Backend::TransitionFn::ID transition_fn_id() const;

private:
  //////////////////////
  // member variables //
  //////////////////////
  
  Backend::TransitionFn::ID transition_fn_id_;
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

/////////////////////////////////////////
// InvalidStateError inlined functions //
/////////////////////////////////////////

/** public */

inline Backend::State::ID InvalidStateError::state_id() const {
  return state_id_;
}

////////////////////////////////////////////////
// InvalidTransitionFnError inlined functions //
////////////////////////////////////////////////

/** public */

inline Backend::TransitionFn::ID InvalidTransitionFnError::transition_fn_id() const {
  return transition_fn_id_;
}

} // namespace Util
} // namespace PlayToLearn
