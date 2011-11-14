/*
 * File: backend/Level.hpp
 */

#pragma once

#include "util/UniqueID.hpp"
#include <string>

namespace PlayToLearn {
namespace Backend {

///////////////////////////
// Level class interface //
///////////////////////////

/**
 * The Level class stores the backend information associated with a level in the
 * game.
 */
class Level {
public:
  /**
   * The Level::ID type represents a uniquely identifier for a particular level.
   */
  typedef Util::UniqueID<Level> ID;
  
  /**
   * The Level constructor populates the level-specific data based on the file
   * specified by the given file name.
   */
  explicit Level(const std::string& level_file_name);

private:
};

} // namespace Backend
} // namespace PlayToLearn
