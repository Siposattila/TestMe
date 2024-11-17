#include "tree_sitter/tree_sitter.h"
#include <iostream>
#include <string>

extern "C" {
TSLanguage *tree_sitter_cpp();
TSLanguage *tree_sitter_java();
TSLanguage *tree_sitter_c_sharp();
}

int main() {
  ts::Language language = tree_sitter_cpp();
  ts::Parser parser{language};

  std::string src = "int main() { return 0; }";
  ts::Tree tree = parser.parseString(src);
  ts::Node root = tree.getRootNode();

  auto treeString = root.getSExpr();
  std::cout << "C++ syntax tree of \n\n int main() { return 0; }\n\n"
            << treeString.get() << "\n\n";

  language = tree_sitter_java();
  parser = ts::Parser{language};

  src = "class Simple{public static void "
        "main(String args[]){System.out.println(\"Hello Java\");}}";
  tree = parser.parseString(src);
  root = tree.getRootNode();

  treeString = root.getSExpr();
  std::cout << "JAVA syntax tree of \n\n class Simple{public static void "
               "main(String args[]){System.out.println(\"Hello Java\");}}\n\n"
            << treeString.get() << "\n\n";

  language = tree_sitter_c_sharp();
  parser = ts::Parser{language};

  src =
      "namespace CSharpTutorials{class Program{static void Main(string[] "
      "args){string message = \"Hello World!!\";Console.WriteLine(message);}}}";
  tree = parser.parseString(src);
  root = tree.getRootNode();

  treeString = root.getSExpr();
  std::cout << "C# syntax tree of \n\n namespace CSharpTutorials{class "
               "Program{static void Main(string[] "
               "args){string message = \"Hello "
               "World!!\";Console.WriteLine(message);}}}\n\n"
            << treeString.get() << "\n\n";
}
