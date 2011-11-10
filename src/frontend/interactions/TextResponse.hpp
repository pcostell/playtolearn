/*
 * File: frontend/interactions/TextResponse.hpp
 */

#pragma once

#include "frontend/interactions/InteractionResponse.hpp"
#include <string>

namespace PlayToLearn {
namespace Frontend {

//////////////////////////////////
// TextResponse class interface //
//////////////////////////////////

/**
 * The TextResponse class represents a specific type of InteractionResponse
 * where the response is simply text to be printed for the user's reading
 * pleasure.
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
   * The TextResponse constructor creates an TextResponse object populated with
   * information supplied by the specified AttributeMap.
   */
  explicit TextResponse(const Backend::AttributeMap& data);
  
  /**
   * type returns what kind of interaction this response represents. This
   * version always returns IR_TEXT.
   */
  Type type() const;
  
  /**
   * text returns the string which represents the text that should be printed
   * for this particular response.
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

} // namespace Frontend
} // namespace PlayToLearn
