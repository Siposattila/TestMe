#pragma once

#include <string>

class Meta {
public:
  Meta(std::string name) : mName(name) {}

  std::string getName() { return mName; }
  void setName(const std::string &name);

protected:
  std::string mName;
};
