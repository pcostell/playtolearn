/*
 * File: backend/StateMachine.hpp
 */

#pragma once

#include "backend/State.hpp"
#include "backend/TransitionFn.hpp"
#include <stdexcept>
#include <map>

namespace PlayToLearn {
namespace Backend {

//////////////////////////////////
// StateMachine class interface //
//////////////////////////////////

/**
 * The StateMachine class represents the DFA which describes the game player's
 * current progress and the setup of the game.
 */
class StateMachine {
public:
  /**
   * current_state_id returns the ID of the player's current state.
   */
  State::ID current_state_id() const;
  
  /**
   * current_state returns the player's actual current state. Both a const and a
   * non-const version are provided.
   */
  const State& current_state() const;
  State& current_state();
  
  /**
   * set_current_state sets the player's current state.
   */
  void set_current_state(State::ID id);
  
  /**
   * contains_state returns true if and only if a State object with the
   * specified ID exists in the state map.
   */
  bool contains_state(State::ID id) const;
  
  /**
   * state_fn returns a reference to the state with the specified ID. If no such
   * state exists, the function throws a InvalidStateError exception. Both a
   * const and a non-const version are provided.
   */
  const State& state(State::ID id) const;
  State& state(State::ID id);
  
  /**
   * add_state adds the specified state. It does nothing if a state with the
   * same ID already exists.
   */
  void add_state(const State& state);
  
  /**
   * remove_state removes the state with the specified ID from the map. It does
   * nothing if the ID doesn't already exist in the map.
   */
  void remove_state(State::ID id);
  
  /**
   * contains_transition_fn returns true if and only if a TransitionFn object
   * with the specified ID exists in the transition function map.
   */
  bool contains_transition_fn(TransitionFn::ID id) const;
  
  /**
   * transition_fn returns a reference to the transition function with the
   * specified id. If no such transition function exists, the function throws a
   * InvalidTransitionFnError exception. Both a const and a non-const version
   * are provided.
   */
  const TransitionFn& transition_fn(TransitionFn::ID id) const;
  TransitionFn& transition_fn(TransitionFn::ID id);
  
  /**
   * add_transition_fn adds the specified transition function. It does nothing
   * if a transition function with the same ID already exists.
   */
  void add_transition_fn(const TransitionFn& transition_fn);
  
  /**
   * remove_transition_fn removes the transition function with the specified ID
   * from the map. It does nothing if the ID doesn't already exist in the map.
   */
  void remove_transition_fn(TransitionFn::ID id);
  
private:
  //////////////////////
  // member variables //
  //////////////////////
  
  State::ID current_state_id_;
  
  std::map<State::ID, State> state_map_;
  
  std::map<TransitionFn::ID, TransitionFn> transition_fn_map_;
};

///////////////////////////////////////
// InvalidStateError class interface //
///////////////////////////////////////

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
  InvalidStateError(const std::string& what_arg, State::ID id);
  
  /**
   * state_id returns the ID of the state which caused the exception to be
   * thrown.
   */
  State::ID state_id() const;

private:
  //////////////////////
  // member variables //
  //////////////////////
  
  State::ID state_id_;
};

//////////////////////////////////////////////
// InvalidTransitionFnError class interface //
//////////////////////////////////////////////

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
  InvalidTransitionFnError(const std::string& what_arg, TransitionFn::ID id);
  
  /**
   * transition_fn_id returns the ID of the transition function which caused the
   * exception to be thrown.
   */
  TransitionFn::ID transition_fn_id() const;

private:
  //////////////////////
  // member variables //
  //////////////////////
  
  TransitionFn::ID transition_fn_id_;
};

////////////////////////////////////
// StateMachine inlined functions //
////////////////////////////////////

/** public */

inline State::ID StateMachine::current_state_id() const {
  return current_state_id_;
}

inline const State& StateMachine::current_state() const {
  return state(current_state_id_);
}

inline State& StateMachine::current_state() {
  return state(current_state_id_);
}

inline void StateMachine::set_current_state(State::ID id) {
  current_state_id_ = id;
}

inline bool StateMachine::contains_state(State::ID id) const {
  return state_map_.count(id);
}

inline State& StateMachine::state(State::ID id) {
  const StateMachine& const_this = *this;
  return const_cast<State&>(const_this.state(id));
}

inline void StateMachine::add_state(const State& state) {
  state_map_.insert(std::make_pair(state.id(), state));
}

inline void StateMachine::remove_state(State::ID id) {
  state_map_.erase(id);
}

inline bool StateMachine::contains_transition_fn(TransitionFn::ID id) const {
  return transition_fn_map_.count(id);
}

inline TransitionFn& StateMachine::transition_fn(TransitionFn::ID id) {
  const StateMachine& const_this = *this;
  return const_cast<TransitionFn&>(const_this.transition_fn(id));
}

inline void StateMachine::add_transition_fn(const TransitionFn& transition_fn) {
  transition_fn_map_.insert(std::make_pair(transition_fn.id(), transition_fn));
}

inline void StateMachine::remove_transition_fn(TransitionFn::ID id) {
  transition_fn_map_.erase(id);
}

/////////////////////////////////////////
// InvalidStateError inlined functions //
/////////////////////////////////////////

/** public */

inline State::ID InvalidStateError::state_id() const {
  return state_id_;
}

////////////////////////////////////////////////
// InvalidTransitionFnError inlined functions //
////////////////////////////////////////////////

/** public */

inline TransitionFn::ID InvalidTransitionFnError::transition_fn_id() const {
  return transition_fn_id_;
}

} // namespace Backend
} // namespace PlayToLearn
