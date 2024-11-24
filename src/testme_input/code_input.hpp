#pragma once

#include "input.hpp"
#include <string>
#include <testme_tree_sitter/testme_tree_sitter.h>
#include <unordered_map>

extern "C" {
TSLanguage *tree_sitter_cpp();
TSLanguage *tree_sitter_java();
TSLanguage *tree_sitter_c_sharp();
}

class CodeInput : public Input {
public:
  CodeInput(std::string filename);

  void processInput() override;
  const std::string getTreeString();

private:
  ts::Language mLanguage;
  ts::Parser mParser;
  ts::Tree mTree;
  std::unordered_map<std::string, TSLanguage *> mSupportedLanguages;

  TSLanguage *getSupportedLanguage();
  void setLanguage();
  void parse();
};
