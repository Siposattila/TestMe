#pragma once

#include <string>

class Meta {
public:
  Meta(std::string name) : mName(name) {}

  std::string getName() { return mName; }

protected:
  std::string mName;
};
