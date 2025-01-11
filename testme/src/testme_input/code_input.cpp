#include "code_input.hpp"
#include "code_input_unsupported_exception.hpp"
#include "input.hpp"
#include <optional>
#include <testme_tree_sitter/testme_tree_sitter.h>
#include <vector>

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
    throw CodeInputUnsupportedException(
        CodeInputUnsupportedException::ErrorNotSupported);
  }

  return mSupportedLanguages.find(extension)->second;
}

const Language CodeInput::getLanguage() { return mTree.getLanguage(); }

const std::string CodeInput::getParsedCode() {
  return std::string(mTree.getRootNode().getSExpr().get());
}

const std::string CodeInput::getParsedCodeByNode(ts::Node node) {
  return std::string(node.getSExpr().get());
}

const std::string CodeInput::getCodeByNode(ts::Node node) {
  return std::string(node.getSourceRange(getInput()));
}

void CodeInput::setLanguage() { mLanguage = getSupportedLanguage(); }

void CodeInput::parse() {
  mParser = ts::Parser{mLanguage};
  mTree = mParser.parseString(getInput());
}

const std::optional<Node> CodeInput::findNode(const Node &node,
                                              std::string_view source,
                                              std::string type,
                                              std::string name) {
  Cursor cursor = node.getCursor();
  if (!cursor.gotoFirstChild()) {
    return std::nullopt;
  }

  std::optional<Node> resultNode = std::nullopt;
  do {
    Node child = cursor.getCurrentNode();
    if (child.getType() == type && child.getSourceRange(source) == name) {
      resultNode = child;
    } else {
      resultNode = findNode(child, source, type, name);
    }
  } while (cursor.gotoNextSibling() && resultNode == std::nullopt);

  return resultNode;
}

void CodeInput::findNodes(const Node &node, std::vector<Node> *resultNodes,
                          std::string_view source, std::string type,
                          std::string name) {
  Cursor cursor = node.getCursor();
  if (!cursor.gotoFirstChild()) {
    return;
  }

  do {
    Node child = cursor.getCurrentNode();
    if (child.getType() == type && child.getSourceRange(source) == name) {
      resultNodes->push_back(child);
    }

    findNodes(child, resultNodes, source, type, name);
  } while (cursor.gotoNextSibling());
}

const std::vector<Node> CodeInput::findNodesByName(std::string name) {
  std::vector<Node> nodes;
  findNodes(mTree.getRootNode(), &nodes, getInput(), "identifier", name);

  return nodes;
}

const Node CodeInput::findFirstNodeByName(std::string name) {
  return findNode(mTree.getRootNode(), getInput(), "identifier", name)
      .value_or(Node{TSNode()});
}
