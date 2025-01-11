#pragma once

#include <exception>

class CodeInputUnsupportedException : public std::exception {
public:
  CodeInputUnsupportedException(const char *message = ErrorUnexpected)
      : mMessage(message) {}
  ~CodeInputUnsupportedException() = default;

  static constexpr char ErrorUnexpected[] = "Error: unexpected error!";
  static constexpr char ErrorNotSupported[] = "Error: not supported language!";

  const char *what() { return mMessage; }

private:
  const char *mMessage;
};
