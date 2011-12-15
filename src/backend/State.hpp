/*
 * File: backend/State.hpp
 */

#pragma once

#include <string>
#include <set>
#include <map>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>

#include "util/UniqueID.hpp"

namespace PlayToLearn {
namespace Backend {

/** class declarations */

class Object;
class TransitionFn;

/** class definitions */

// The State class represents the player's DFA state at any point in time 
// throughout the game.
class State {
public:
  // The State::ID type represents a unique identifier for a particular state.
  typedef Util::UniqueID<State> ID;
  
  // object_iterator and const_object_iterator define iterators over the object-
  // -transition function mappings associated with this state.
  typedef std::map<Util::UniqueID<Object>, Util::UniqueID<TransitionFn> >::iterator object_iterator;
  typedef std::map<Util::UniqueID<Object>, Util::UniqueID<TransitionFn> >::const_iterator const_object_iterator;
  
  // The State constructor initializes a State object with the specified unique
  // identifier.
  explicit State(ID = ID());
  
  // id returns the unique ID of this particular state object.
  ID id() const;
  
  // contains_object returns true if and only if the transition function with
  // the specified ID is in this state's object map.
  bool contains_object(Util::UniqueID<Object> id) const;
  
  // transition_fn returns the transition function associated with this state/
  // object pair. If no such object_id exists, the function will throw an
  // InvalidObjectError exception.
  Util::UniqueID<TransitionFn> transition_fn_id(Util::UniqueID<Object> object_id) const;
  
  // insert_object inserts the object ID and transition function ID
  // into this state's map.
  void insert_object(Util::UniqueID<Object> object_id, Util::UniqueID<TransitionFn> fn_id);
  
  // remove_object removes the object ID from this state's map.
  void remove_object(Util::UniqueID<Object> id);
  
  // object_begin returns an iterator to the beginning of the internal set of
  // Object objects this state stores. Both a const and a non-const version
  // are supplied.
  const_object_iterator object_begin() const;
  object_iterator object_begin();
  
  // object_end returns an iterator to the end of the internal set of
  // Object objects this state stores. Both a const and a non-const version
  // are supplied.
  const_object_iterator object_end() const;
  object_iterator object_end();
  
  // serialize reads or writes the underlying ID and map using Boost's
  // serialization library.
  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version);

private:
  // member variables
  ID id_;
  std::map<Util::UniqueID<Object>, Util::UniqueID<TransitionFn> > object_ids_;
};

/** State inlined member functions, public */

inline State::ID State::id() const {
  return id_;
}

inline State::const_object_iterator State::object_begin() const {
  return object_ids_.begin();
}

inline State::object_iterator State::object_begin() {
  return object_ids_.begin();
}

inline State::const_object_iterator State::object_end() const {
  return object_ids_.end();
}

inline State::object_iterator State::object_end() {
  return object_ids_.end();
}

/** State template member functions, public */

template <typename Archive>
void State::serialize(Archive& ar, const unsigned int version) {
  ar & boost::serialization::make_nvp("id", id_);
  ar & boost::serialization::make_nvp("object_ids", object_ids_);
}

} // namespace Backend
} // namespace PlayToLearn
