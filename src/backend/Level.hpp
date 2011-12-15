/*
 * File: backend/Level.hpp
 */

#pragma once

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/nvp.hpp>

#include "util/UniqueID.hpp"

namespace PlayToLearn {
namespace Backend {

/** class declarations */

class State;

/** class definitions */

// The Level class stores all relevant information associated with a particular
// level.
class Level {
public:
  // The Level::ID type represents a unique identifier for a particular level.
  typedef Util::UniqueID<Level> ID;
  
  // The Level constructor accepts the ID of the initial state for this level.
  explicit Level(ID id = ID());
  
  // initial_state returns the ID of the initial state for this level.
  Util::UniqueID<State> initial_state() const;
  
  // set_initial_state changes the initial state for this level to the one with
  // the specified ID.
  void set_initial_state(Util::UniqueID<State> initial_state);
  
  // serialize reads or writes the underlying ID and initial state using Boost's
  // serialization library.
  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version);

private:
  // member variables
  ID id_;
  Util::UniqueID<State> initial_state_;
};

/** Level inlined member functions, public */

inline Util::UniqueID<State> Level::initial_state() const {
  return initial_state_;
}

inline void Level::set_initial_state(Util::UniqueID<State> initial_state) {
  initial_state_ = initial_state;
}

/** Level template member functions, public */
template <typename Archive>
void Level::serialize(Archive& ar, const unsigned int version) {
  ar & boost::serialization::make_nvp("id", id_);
  ar & boost::serialization::make_nvp("initial_state", initial_state_);
}

} // namespace Backend
} // namespace PlayToLearn
