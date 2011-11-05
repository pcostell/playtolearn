/*
 * File: TextInteractionResponse.hpp
 */

#pragma once

#include "InteractionResponse.hpp"

namespace PlayToLearn {

//////////////////////////////////
// TextResponse class interface //
//////////////////////////////////

/**
 * TODO: comment
 */
class TextResponse : public InteractionResponse {
public:
  /**
   * TODO: comment
   */
  explicit InteractionResponse(const Backend::AttributeMap& data);
  
  /**
   * TODO: comment
   */
  Type type() const;
  
  /**
   * TODO: comment
   */
  const std::string& text() const;

private:
  //////////////////////
  // member variables //
  //////////////////////
  
  std::string text_;
};

////////////////////////////////////
// TextResponse inlined functions //
////////////////////////////////////

/** public */

inline InteractionResponse::Type TextResponse::type() const {
  return IR_TEXT;
}

inline const std::string& TextResponse::text() const {
  return text_;
}

} // namespace PlayToLearn
