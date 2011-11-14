/*
 * File: backend/Level.cpp
 */

#include "backend/Level.hpp"
#include <fstream>

using namespace std;

namespace PlayToLearn {
namespace Backend {

/////////////////////////////////////////
// Level member implementation details //
/////////////////////////////////////////

/** public */

Level::Level(const string& level_file_name) {
  ifstream input_file(level_file_name.c_str());
  
}

} // namespace Backend
} // namespace PlayToLearn
