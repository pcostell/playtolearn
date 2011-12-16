/*
 * File: backend/Engine.hpp
 */

#pragma once

#include <string>
#include <utility>

#include <boost/shared_ptr.hpp>

#include "util/UniqueID.hpp"
#include "backend/AttributeMap.hpp"
#include "backend/StateMachine.hpp"
#include "backend/State.hpp"
#include "backend/TransitionFn.hpp"

namespace PlayToLearn {

/** outside class declarations */

namespace Frontend {
  class Interaction;
  class InteractionPrompt;
}

namespace Backend {

/** class declarations */

class Object;

/** class definitions */

// The Engine class drives the entire backend portion of the program.
class Engine {
public:
  // The Engine constructor accepts a single level index as an argument. It
  // initializes the backend starting at the specified level in the specified
  // initial state.
  explicit Engine(int initial_level_index, State::ID initial_state_id);
  
  // load_level instructs the game engine to load all of the data associated
  // with a particular level of the game. If any of the TransitionFn objects in
  // this level attempt to utilize an unsupported script type, an
  // InvalidScriptTypeError exception is thrown.
  void load_level(int level_index);
  
  // player_x and player_y return the x and y coordinates of the player's
  // current location, respectively.
  double player_x() const;
  double player_y() const;
  
  // move_player modifies the player's location by the specified x and y
  // distances.
  void move_player(double dx, double dy);
  
  // request_interaction retrieves the interaction data associated with the
  // specified interactive object while in the current state. It will return
  // a NULL smart pointer if no such data exists.
  boost::shared_ptr<Frontend::InteractionPrompt> request_interaction(Util::UniqueID<Object> id) const;
  
  // register_interaction handles the backend processing required when the user
  // interacts with some object in the game world. It returns the response, as
  // determined by the global map modified by the potential script.
  std::string register_interaction(boost::shared_ptr<Frontend::Interaction> interaction);

private:
  // member variables
  
  StateMachine state_machine_;
  double player_x_;
  double player_y_;
  AttributeMap global_state_;
  
  std::map<TransitionFn::ID, AttributeMap> transition_data_;
  
  // member functions
  
  void load_state_machine(const std::string& level_name);
  void load_transition_data(const std::string& level_name);
  void load_transition_fns(const std::string& level_name);
  void load_python_transition_fn_script(int transition_fn_id, const std::string& script_name);
};

/** Engine inlined member functions, public */

inline double Engine::player_x() const {
  return player_x_;
}

inline double Engine::player_y() const {
  return player_y_;
}

inline void Engine::move_player(double dx, double dy) {
  player_x_ += dx;
  player_y_ += dy;
}

} // namespace Backend
} // namespace PlayToLearn
