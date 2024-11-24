#include "code_input.hpp"
#include "code_input_unsupported_exception.hpp"
#include "input.hpp"
#include <optional>
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

const ts::Tree *CodeInput::getTree() { return &mTree; }

const std::string CodeInput::getTreeString() {
  return std::string(mTree.getRootNode().getSExpr().get());
}

void CodeInput::setLanguage() { mLanguage = getSupportedLanguage(); }

void CodeInput::parse() {
  mParser = ts::Parser{mLanguage};
  mTree = mParser.parseString(getInput());
}

const std::optional<ts::Node> CodeInput::findNode(const ts::Node &root,
                                                  std::string name) {
  for (const auto &child : ts::Children{root}) {
    // Check if the node type is "class"
    if (child.getType() == "class") {
      // Retrieve the name of the class (assuming it's a named field or a direct
      // child)
      ts::Node nameNode = child.getChildByFieldName("name");
      // if (!nameNode.isNull() && nameNode.) {
      //   return child; // Found the node
      // }
    }

    // Recursively search in the child nodes
    if (auto result = findNode(child, name)) {
      return result;
    }
  }

  return std::nullopt;
}
