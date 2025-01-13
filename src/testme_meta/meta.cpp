#include "meta.hpp"

Meta::Meta(std::string name) : mName(name) {}

std::string Meta::getName() { return mName; }

void Meta::setName(const std::string &name) { mName = name; }
