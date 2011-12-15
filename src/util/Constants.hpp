/*
 * File: util/Constants.hpp
 */

#pragma once

#include <string>

#include "util/UniqueID.hpp"

namespace PlayToLearn {

/** outside class declarations */

namespace Backend {
  class Object;
}

namespace Util {

/** AttributeMap attribute name constants */

// The kStateIDAttribute constant represents the name of the attribute that
// should be paired with the corresponding text field needed by a TextPrompt
// object.
const std::string kStateIDAttribute("state_id");

// The kObjectIDAttribute constant represents the name of the attribute that
// should be paired with the corresponding object ID involved in an interaction.
const std::string kObjectIDAttribute("object_id");

// The kInteractionPromptType attribute represents the name of the attribute
// that should be paired with the type of InteractionPrompt object described
// by the AttributeMap which contains the related data. See the below constants
// for the corresponding values.
const std::string kInteractionPromptTypeAttribute("interaction_prompt_type");

// The kTextAttribute constant represents the name of the attribute that should
// be paired with text describing a question or dialog.
const std::string kTextAttribute("text");

// The kFreeResponseAnswerAttribute constant represents the name of the
// attribute that should be paired with text describing a user's answer to a
// free response question.
const std::string kFreeResponseAnswerAttribute("free_response_answer");

// The kNumMCChoicesAttribute constant represents the name of the attribute that
// should be paired with an integer describing how many choices are available
// for a multiple choice question.
const std::string kNumMCChoicesAttribute("num_mc_choices");

// The kMCChoiceAttribute constant represents the prefix of the name of the
// attribute that should be paired with text describing a multiple choice
// option. The string should be followed by a number representing that choice's
// index in the list of options.
const std::string kMCChoiceAttribute("mc_choice_");

// The kMCAnswerAttribute constant represents the name of the attribute that
// should be paired with the integer representing a user's selection in response
// to a multiple choice question.
const std::string kMCAnswerIndexAttribute("mc_answer_index");

/** AttributeMap value constants */

// The following constants represent the various values associated with the
// interaction prompt type attribute for different InteractionPrompt subclasses.
// They should be paired with kInteractionPromptTypeAttribute.
const std::string kTextPromptTypeValue("text_prompt");
const std::string kFreeResponsePromptTypeValue("free_response_prompt");
const std::string kMultipleChoicePromptTypeValue("multiple_choice_prompt");
const std::string kNewLevelPromptTypeValue("new_level_prompt");

/** Object constants */

// kDefaultObject is a constant which represents the ID of an interactive object
// that should automatically be interacted with upon entering a state.
const UniqueID<Backend::Object> kDefaultObject(-2);

/** TransitionFn constants */

// The kTransitionFnScriptFunctionName constant represents the name of the
// script function which performs the transition function operation.
const std::string kTransitionFnScriptFunctionName("state_transition_");

/** Engine constants */

// The kLevelDirectoryPrefix constant represents the file prefix of all level
// folders in the game. The prefix is followed by the index of the level.
const std::string kLevelDirectoryPrefix("data/level");

// The kLevelStateMachineFile constant represents the name of the file
// containing StateMachine information for a particular level.
const std::string kLevelStateMachineFile("sm.xml");

// The kLevelTransitionDataFile constant represents the name of the file
// containing transition data information for a particular level.
const std::string kLevelTransitionDataFile("tdata.xml");

// The kLevelTransitionFnFile constant represents the name of the file
// containing information regarding all transition function external scripts in
// a particular level.
const std::string kLevelTransitionFnFile("tfn.dat");

// The kLevelTransitionFnScriptDirectory constant represents the name of the
// directory containing all of the transition function scripts for a particular
// level.
const std::string kLevelTransitionFnScriptDirectory("tfn_scripts/");

/** scripting constants */

// The kPythonExtension constant represents the file extension used to store
// Python scripts.
const std::string kPythonExtension("py");

} // namespace Util
} // namespace PlayToLearn
