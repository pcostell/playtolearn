/*
 * File: util/Constants.hpp
 */

#pragma once

#include <string>

namespace PlayToLearn {
namespace Util {

////////////////////////
// UniqueID constants //
////////////////////////

/**
 * kInvalid is a constant which represents an invalid ID's integer.
 */
const int kInvalidID = -1;

///////////////////////////////////////////
// AttributeMap attribute name constants //
///////////////////////////////////////////

/**
 * The kStateIDAttribute constant represents the name of the attribute that
 * should be paired with the corresponding text field needed by a TextResponse
 * object.
 */
const std::string kStateIDAttribute("state_id");

/**
 * The kObjectIDAttribute constant represents the name of the attribute that
 * should be paired with the corresponding object ID involved in an interaction.
 */
const std::string kObjectIDAttribute("object_id");

/**
 * The kTextAttribute constant represents the name of the attribute that should
 * be paired with text describing a question or dialog.
 */
const std::string kTextAttribute("text");

/**
 * The kFreeResponseAnswerAttribute constant represents the name of the
 * attribute that should be paired with text describing a user's answer to a
 * free response question.
 */
const std::string kFreeResponseAnswerAttribute("free_response_answer");

/**
 * The kNumMCChoicesAttribute constant represents the name of the attribute that
 * should be paired with an integer describing how many choices are available
 * for a multiple choice question.
 */
const std::string kNumMCChoicesAttribute("num_mc_choices");

/**
 * The kMCChoiceAttribute constant represents the prefix of the name of the
 * attribute that should be paired with text describing a multiple choice
 * option. The string should be followed by a number representing that choice's
 * index in the list of options.
 */
const std::string kMCChoiceAttribute("mc_choice_");

} // namespace Util
} // namespace PlayToLearn
