/*
 * File: backend/State.hpp
 */

#pragma once

#include "util/UniqueID.hpp"
#include "backend/TransitionFn.hpp"
#include "backend/Object.hpp"
#include <string>
#include <set>
#include <map>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>

namespace PlayToLearn {
namespace Backend {

///////////////////////////
// State class interface //
///////////////////////////

/**
 * The State class represents the player's DFA state at any point in time 
 * throughout the game.
 */
class State {
public:
  /**
   * The State::ID type represents a uniquely identifier for a particular state.
   */
  typedef Util::UniqueID<State> ID;
  
  /**
   * object_iterator and const_object_iterator define iterators over the object-
   * -transition function mappings associated with this state.
   */
  typedef std::map<Object::ID, TransitionFn::ID>::iterator object_iterator;
  typedef std::map<Object::ID, TransitionFn::ID>::const_iterator const_object_iterator;
  
  /**
   * The State constructor initializes a State object with the specified unique
   * identifier.
   */
  explicit State(ID id = ID());
  
  /**
   * id returns the unique ID of this particular state object.
   */
  ID id() const;
  
  /**
   * object_exists returns true if and only if the transition function with
   * the specified ID is in this state's object map.
   */
  bool object_exists(Object::ID id) const;
  
  /**
   * transition_fn returns the transition function associated with this state/
   * object pair. If no such object_id exists, the function will throw an
   * InvalidObjectError exception.
   */
  TransitionFn::ID transition_fn_id(Object::ID object_id) const;
  
  /**
   * insert_object inserts the object ID and transition function ID
   * into this state's map.
   */
  void insert_object(Object::ID object_id, TransitionFn::ID fn_id);
  
  /**
   * remove_object removes the object ID from this state's map.
   */
  void remove_object(Object::ID id);
  
  /**
   * object_begin returns an iterator to the beginning of the internal set of
   * Object objects this state stores. Both a const and a non-const version
   * are supplied.
   */
  const_object_iterator object_begin() const;
  object_iterator object_begin();
  
  /**
   * object_end returns an iterator to the end of the internal set of
   * Object objects this state stores. Both a const and a non-const version
   * are supplied.
   */
  const_object_iterator object_end() const;
  object_iterator object_end();
  
  /**
   * serialize reads or writes the underlying ID and map using Boost's
   * serialization library.
   */
  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version);

private:
  //////////////////////
  // member variables //
  //////////////////////
  
  ID id_;
  
  std::map<Object::ID, TransitionFn::ID> object_ids_;
};

/////////////////////////////
// State inlined functions //
/////////////////////////////

/** public */

inline State::ID State::id() const {
  return id_;
}

inline bool State::object_exists(Object::ID id) const {
  return object_ids_.count(id);
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

/////////////////////////////////////
// State template member functions //
/////////////////////////////////////

/** public */

template <typename Archive>
void State::serialize(Archive& ar, const unsigned int version) {
  ar & boost::serialization::make_nvp("id", id_);
  ar & boost::serialization::make_nvp("object_ids", object_ids_);
}

} // namespace Backend
} // namespace PlayToLearn
