/*
 * File: midend/GenericInteraction.cpp
 */

#include "midend/GenericInteraction.hpp"

using namespace std;

namespace PlayToLearn {
namespace Midend {

//////////////////////////////////////////////////////
// GenericInteraction member implementation details //
//////////////////////////////////////////////////////

/** public */

GenericInteraction::GenericInteraction(Backend::Object::ID object_id) :
  Interaction(object_id)
{
  // empty body
}

} // namespace Midend
} // namespace PlayToLearn
