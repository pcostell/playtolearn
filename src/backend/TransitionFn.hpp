/*
 * File: backend/TransitionFn.hpp
 */

#pragma once

#include "util/UniqueID.hpp"
//#include "backend/PythonTransitionFn.hpp"
#include "backend/AttributeMap.hpp"
#include <string>
#include <boost/scoped_ptr.hpp>

namespace PlayToLearn {
namespace Backend {

////////////////////////
// class declarations //
////////////////////////

class State;

//////////////////////////////////
// TransitionFn class interface //
//////////////////////////////////

/**
 * The TransitionFn class represents a transition function which describes how
 * to go from one state to another given some interaction.
 */
class TransitionFn {
public:
  /**
   * The TransitionFn::ID type represents a uniquely identifier for a particular
   * transition function.
   */
  typedef Util::UniqueID<TransitionFn> ID;
  
  /**
   * The TransitionFn constructor initializes a TransitionFn object with the
   * specified unique identifier.
   */
  explicit TransitionFn(ID id);
  
  /**
   * id returns the unique ID of this particular transition function object.
   */
  ID id() const;
  
  /**
   * set_python_fn sets the underlying python script to the code passed in as
   * a string object. That code will be executed the next time the underlying
   * PythonTransitionFn object is invoked.
   */
  void set_python_fn(const std::string& python_code);
  
  /**
   * reset_python_fn erases the underlying python script and sets the internal
   * PythonTransitionFn pointer to NULL.
   */
  void reset_python_fn();
  
  /**
   * next_state returns the ID of the next state based on the given interaction
   * elements and environmental status. interaction is an map of attributes
   * containing all of the data which describes the transition action.
   */
  Util::UniqueID<State> next_state(const AttributeMap& interaction) const;

private:
  //////////////////////
  // member variables //
  //////////////////////
  
  ID id_;
  
  //boost::scoped_ptr<PythonTransitionFn> python_fn_;
};

////////////////////////////////////
// TransitionFn inlined functions //
////////////////////////////////////

/** public */

inline TransitionFn::ID TransitionFn::id() const {
  return id_;
}

inline void TransitionFn::set_python_fn(const std::string& python_code) {
  //python_fn_.reset(new PythonTransitionFn(python_code));
}

inline void TransitionFn::reset_python_fn() {
  //python_fn_.reset();
}

} // namespace Backend
} // namespace PlayToLearn
