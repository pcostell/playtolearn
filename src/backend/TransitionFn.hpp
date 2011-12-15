/*
 * File: backend/TransitionFn.hpp
 */

#pragma once

#include <string>
#include <vector>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/shared_ptr.hpp>

#include "util/UniqueID.hpp"

namespace PlayToLearn {
namespace Backend {

/** class declarations */

class AttributeMap;
class State;
class ExternalTransitionFn;

/** class definitions */

// The TransitionFn class represents a transition function which describes how
// to go from one state to another given some interaction.
class TransitionFn {
public:
  // The TransitionFn::ID type represents a unique identifier for a particular
  // transition function.
  typedef Util::UniqueID<TransitionFn> ID;
  
  // The TransitionFn constructor initializes a TransitionFn object with the
  // specified unique identifier.
  explicit TransitionFn(ID id = ID());
  
  // id returns the unique ID of this particular transition function object.
  ID id() const;
  
  // num_states returns the number of states to which this transition function
  // may apply.
  int num_states() const;
  
  // state_at returns the state ID associated with the state at the specified
  // index. The index must be non-negative and less than num_states; otherwise,
  // state_at throws a InvalidStateIndexError exception.
  Util::UniqueID<State> state_at(int index) const;
  
  // add_state adds a new state ID to the list of states to which this
  // transition function is able to move.
  void add_state(Util::UniqueID<State> state_id);
  
  // remove_state removes the state ID at the specified index from this
  // transition function's list of reachable states. If the index is out of
  // bounds, the function throws a InvalidStateIndexError exception.
  void remove_state(int index);
  
  // set_python_function changes the internal ExternalTransitionFn script to be
  // a PythonTransitionFn object with the specified code and function name.
  void set_python_function(const std::string& python_code);
  
  // next_state returns the ID of the next state based on the given interaction
  // elements and environmental status. interaction is an map of attributes
  // containing all of the data which describes the transition action.
  // global_state is a modifiable map containing state pertaining to the game
  // world which the transition scripts can update. If the transition function
  // has not yet been assigned a transition script, the function throws a
  // MissingTransitionFnScriptError exception.
  Util::UniqueID<State> next_state(const AttributeMap& interaction, AttributeMap& global_state) const;
  
  // serialize reads or writes the underlying ID using Boost's serialization
  // library.
  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version);

private:
  // member variables
  ID id_;
  std::vector<Util::UniqueID<State> > state_ids_;
  boost::shared_ptr<ExternalTransitionFn> script_fn_;
  
  // member functions
  void check_state_index(int index) const;
};

/** TransitionFn inlined member functions, public */

inline TransitionFn::ID TransitionFn::id() const {
  return id_;
}

inline int TransitionFn::num_states() const {
  return static_cast<int>(state_ids_.size());
}

/** TransitionFn template member functions, public */

template <typename Archive>
void TransitionFn::serialize(Archive& ar, const unsigned int version) {
  ar & boost::serialization::make_nvp("id", id_);
  ar & boost::serialization::make_nvp("state_ids", state_ids_);
}

} // namespace Backend
} // namespace PlayToLearn
