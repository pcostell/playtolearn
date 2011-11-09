/*
 * File: backend/Engine.hpp
 */

#pragma once

#include "frontend/Interaction.hpp"
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
   * register_interaction handles the backend processing required when the user
   * interacts with some object in the game world. It returns a pointer to the
   * InteractionResponse object associated with the interaction request.
   */
  Frontend::InteractionResponse::Ptr register_interaction(Frontend::Interaction::Ptr interaction);

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
