# How to build
You will need cmake. To be exact atleast cmake version 3.22.

```shell
cmake -B build
cd build
make
```

Thats it!

After you change something just run ```make``` in the build folder.

# How to test
When you build with `make` then the tests are built as well.

This project is using [gtest](https://github.com/google/googletest) v1.14.0.

After the build is complete then you just run ```make test```.

# Tree-sitter
This project is using [tree-sitter](https://github.com/tree-sitter/tree-sitter) v0.22.6.

## Tree-sitter grammar
- [tree-sitter-cpp](https://github.com/tree-sitter/tree-sitter-cpp) v0.22.2
- [tree-sitter-java](https://github.com/tree-sitter/tree-sitter-java) v0.21.2
- [tree-sitter-c-sharp](https://github.com/tree-sitter/tree-sitter-c-sharp) v0.21.0
