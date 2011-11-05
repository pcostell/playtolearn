/*
 * File: compile-test.cpp
 * This file provides code to ensure that all of the code for the backend
 * compiles, as well as some basic tests.
 */

#include "../src/backend/UniqueID.hpp"
#include "../src/backend/AttributeMap.hpp"
#include "../src/backend/State.hpp"
#include "../src/backend/TransitionFn.hpp"
#include "../src/backend/StateMachine.hpp"
#include "../src/backend/Engine.hpp"

using namespace std;
using namespace PlayToLearn::Backend;

int main(int arc, char** argv) {
  Engine engine;
  StateMachine state_machine;
  AttributeMap attr_map;
  
  return 0;
}
