# How to build
The project is using `clang 18.1.3`.
You will need cmake. To be exact atleast `cmake version 3.22`.

You need to use `pre-commit` for this project.
Before you are trying to use pre-commit you need to make sure that you have these installed:
- `clang-format`

On linux you can just pretty much use `apt` to install them.

On how to install and use `pre-commit` please refer to the [pre-commit section](#pre-commit).

```shell
cmake -B build
cd build
make
```

Thats it!

After you change something just run `make` in the build folder.

# How to test
When you build with `make` then the tests are built as well.

This project is using [gtest](https://github.com/google/googletest) v1.14.0.

After the build is complete then you just run `ctest`.

# Pre-commit
To provide a good quality code for the project it is mandatory to use [pre-commit](https://pre-commit.com).

To install you need to have python on your system. After that just run `pip install pre-commit`.

Before you are all set with pre-commit you need to install the hooks in your local repo.
You can do that with this command `pre-commit install`.

Good! Now you are all set from now on pre-commit will automatically run every time when you are trying to make a commit.

You can always check with pre-commit that your changes will fail or not before making a commit.
Just run: `pre-commit`

# Tree-sitter
This project is using [tree-sitter](https://github.com/tree-sitter/tree-sitter) v0.22.6.

## Tree-sitter grammar
- [tree-sitter-cpp](https://github.com/tree-sitter/tree-sitter-cpp) v0.22.2
- [tree-sitter-java](https://github.com/tree-sitter/tree-sitter-java) v0.21.2
- [tree-sitter-c-sharp](https://github.com/tree-sitter/tree-sitter-c-sharp) v0.21.0
