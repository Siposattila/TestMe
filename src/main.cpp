#include "testme_tree_sitter/testme_tree_sitter.h"
#include <iostream>
#include <testme_input/code_input.hpp>

void iterateAllChildrenWithCursor(const ts::Node &node,
                                  std::string_view source) {
  ts::Cursor cursor = node.getCursor();

  if (!cursor.gotoFirstChild()) {
    std::cout << "No children found for node: " << node.getType() << std::endl;
    return;
  }

  do {
    ts::Node child = cursor.getCurrentNode();

    std::cout << "Child Type: " << child.getType() << std::endl;
    std::cout << "Child Source: " << child.getSourceRange(source) << std::endl
              << std::endl;

    iterateAllChildrenWithCursor(child, source);

  } while (cursor.gotoNextSibling());
}

int main() {
  CodeInput input("data/input/example.cs");
  input.processInput();
  std::cout << input.getTreeString() << std::endl << std::endl << std::endl;

  ts::Node node = input.getTree()->getRootNode();
  iterateAllChildrenWithCursor(node, input.getInput());

  return 0;
}
