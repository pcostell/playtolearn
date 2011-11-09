/*
 * File: backend/Engine.hpp
 */

#pragma once

#include "backend/StateMachine.hpp"
#include <utility>

namespace PlayToLearn {
namespace Backend {

////////////////////////////
// Engine class interface //
////////////////////////////

/**
 * The Engine class drives the entire backend portion of the program.
 */
class Engine {
public:
  /**
   * player_x and player_y return the x and y coordinates of the player's
   * current location, respectively.
   */
  double player_x() const;
  double player_y() const;
  
  /**
   * move_player modifies the player's location by the specified x and y
   * distances.
   */
  void move_player(double dx, double dy);
  
  /**
   * TODO: comment
   */
  const AttributeMap& register_interaction(const AttributeMap& interaction);

private:
  //////////////////////
  // member variables //
  //////////////////////
  
  StateMachine state_machine_;
  
  double player_x_;
  double player_y_;
};

//////////////////////////////
// Engine inlined functions //
//////////////////////////////

/** public */

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
