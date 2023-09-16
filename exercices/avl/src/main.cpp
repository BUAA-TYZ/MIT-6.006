#include <iostream>
#include <gtest/gtest.h>

#include "avl.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout << "RUNNING TESTS ..." << std::endl;
  int ret{RUN_ALL_TESTS()};
  if (!ret)
      std::cout << "<<<SUCCESS>>>" << std::endl;
  else
      std::cout << "FAILED" << std::endl;
}