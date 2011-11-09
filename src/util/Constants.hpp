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
const int kInvalidIDentifier = -1;

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
 * TODO: comment
 */
const std::string kTextAttribute("text");

/**
 * TODO: comment
 */
const std::string kFreeResponseAnswerAttribute("free_response_answer");


} // namespace Util
} // namespace PlayToLearn
