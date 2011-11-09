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
const std::string kStateIDAttribute;

/**
 * The kObjectIDAttribute constant represents the name of the attribute that
 * should be paired with the corresponding object ID involved in an interaction.
 */
const std::string kObjectIDAttribute;

/**
 * TODO: comment
 */
const std::string kTextAttribute;

/**
 * TODO: comment
 */
const std::string kFreeResponseAnswerAttribute;

} // namespace Util
} // namespace PlayToLearn
