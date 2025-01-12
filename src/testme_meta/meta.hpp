#pragma once

#include <string>

class Meta {
public:
  Meta(std::string name);

  std::string getName();
  void setName(const std::string &name);

protected:
  std::string mName;
};
