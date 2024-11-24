#include "input.hpp"
#include <filesystem>
#include <fstream>
#include <ios>
#include <stdexcept>

Input::Input(std::string filename) : mFilename(filename), mInput("") {}

Input::~Input() {}

void Input::readInput() {
  if (!std::filesystem::exists(mFilename)) {
    throw std::invalid_argument(mFilename + " was not found!");
  }

  std::ifstream fileInputStream(mFilename);

  // reserve prealloc string
  fileInputStream.seekg(0, std::ios::end);
  mInput.reserve(fileInputStream.tellg());
  fileInputStream.seekg(0, std::ios::beg);

  // putting all of the file content into mInput
  mInput.assign((std::istreambuf_iterator<char>(fileInputStream)),
                std::istreambuf_iterator<char>());
}

std::string Input::getExtension() {
  std::string extension = "";
  if (mFilename.find_last_of(".") != std::string::npos) {
    extension = mFilename.substr(mFilename.find_last_of("."));
  }

  return extension;
}
