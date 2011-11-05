/*
 * File: State.cpp
 */

#include "State.hpp"

using namespace std;

namespace PlayToLearn {
namespace Backend {

/////////////////////
// State constants //
/////////////////////

/** public */

const string State::kStateIDAttribute("state_id");

/////////////////////////////////////////
// State member implementation details //
/////////////////////////////////////////

/** public */

State::State(ID id) : id_(id) {
  // empty body
}

} // namespace Backend
} // namespace PlayToLearn
