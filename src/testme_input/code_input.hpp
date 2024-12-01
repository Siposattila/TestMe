#pragma once

#include "input.hpp"
#include <optional>
#include <string>
#include <testme_tree_sitter/testme_tree_sitter.h>
#include <unordered_map>
#include <vector>

extern "C" {
TSLanguage *tree_sitter_cpp();
TSLanguage *tree_sitter_java();
TSLanguage *tree_sitter_c_sharp();
}

using namespace ts;

class CodeInput : public Input {
public:
  CodeInput(std::string filename);

  void processInput() override;

  const Language getLanguage();

  const std::string getParsedCode();
  const std::string getParsedCodeByNode(Node node);
  const std::string getCodeByNode(Node node);

  const std::vector<Node> findNodesByName(std::string name);
  const Node findFirstNodeByName(std::string name);

private:
  Language mLanguage;
  Parser mParser;
  Tree mTree;
  std::unordered_map<std::string, TSLanguage *> mSupportedLanguages;

  TSLanguage *getSupportedLanguage();
  void setLanguage();
  void parse();

  const std::optional<Node> findNode(const Node &node, std::string_view source,
                                     std::string type, std::string name);
  void findNodes(const Node &node, std::vector<Node> *resultNodes,
                 std::string_view source, std::string type, std::string name);
};
