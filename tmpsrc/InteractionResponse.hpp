/*
 * File: InteractionResponse.hpp
 */

#pragma once

#include "../backend/AttributeMap.hpp"
#include <string>

namespace PlayToLearn {

/////////////////////////////////////////
// InteractionResponse class interface //
/////////////////////////////////////////

/**
 * TODO: comment
 */
class InteractionResponse {
public:
  /**
   * The type enum describes what kind of interaction this response represents.
   */
  enum Type {
    IR_TEXT,
    IR_FREE_RESPONSE,
    IR_MULTIPLE_CHOICE,
  };
  
  /**
   * TODO: comment
   */
  explicit InteractionResponse(const Backend::AttributeMap& data);
  
  /**
   * TODO: comment
   */
  virtual ~InteractionResponse();
  
  /**
   * TODO: comment
   */
  virtual Type type() const = 0;
};

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
