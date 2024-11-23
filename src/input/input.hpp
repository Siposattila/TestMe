#pragma once

#include <string>

class Input {
public:
  virtual ~Input();
  explicit Input(std::string filename);

  std::string getFilename() { return mFilename; }
  std::string getInput() { return mInput; }
  virtual void processInput() = 0;

protected:
  void readInput();

private:
  std::string mFilename;
  std::string mInput;
};
