
#pragma once

#include <stdexcept>
#include <string>

class Display {
public:
  class Error : public std::runtime_error {
  public:
    explicit Error (const std::string& what) : std::runtime_error(what) {}
  };
  virtual ~Display() {};
  virtual void main_display_loop() {};
};