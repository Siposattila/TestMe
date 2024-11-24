#include "code_input.hpp"
#include "code_input_unsupported_exception.hpp"
#include "input.hpp"
#include <testme_tree_sitter/testme_tree_sitter.h>

CodeInput::CodeInput(std::string filename)
    : Input(filename), mSupportedLanguages(), mLanguage(nullptr),
      mParser(nullptr), mTree(nullptr) {
  mSupportedLanguages.insert({".cs", tree_sitter_c_sharp()});
  mSupportedLanguages.insert({".cpp", tree_sitter_cpp()});
  mSupportedLanguages.insert({".java", tree_sitter_java()});
}

void CodeInput::processInput() {
  setLanguage();
  readInput();
  parse();
}

TSLanguage *CodeInput::getSupportedLanguage() {
  std::string extension = getExtension();
  if (!mSupportedLanguages.contains(extension)) {
    throw CodeInputUnsupportedException::ErrorNotSupported;
  }

  return mSupportedLanguages.find(extension)->second;
}

const std::string CodeInput::getTreeString() {
  return std::string(mTree.getRootNode().getSExpr().get());
}

void CodeInput::setLanguage() { mLanguage = getSupportedLanguage(); }

void CodeInput::parse() {
  mParser = ts::Parser{mLanguage};
  mTree = mParser.parseString(getInput());
}
