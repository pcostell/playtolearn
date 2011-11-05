/*
 * File: TextResponse.hpp
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
   * The Ptr typedef allows us to refer to shared_ptr<TextResponse> smart
   * pointers as TextResponse::Ptr. A const version is provided as well.
   */
  typedef boost::shared_ptr<TextResponse> Ptr;
  typedef boost::shared_ptr<const TextResponse> ConstPtr;
  
  /**
   * TODO: comment
   */
  explicit TextResponse(const Backend::AttributeMap& data);
  
  /**
   * The type enum describes what kind of interaction this response represents.
   * This version always returns IR_TEXT.
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
