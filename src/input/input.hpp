#pragma once

#include <string>

class Input {
public:
  Input(std::string filename);

  std::string getFilename() { return mFilename; }
  std::string getInput() { return mInput; }

protected:
  void readInput();

private:
  std::string mFilename;
  std::string mInput;
};
