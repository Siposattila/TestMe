#include "analyzer.hpp"
#include <cstddef>
#include <string>
#include <vector>

size_t difference(const std::string &actual, const std::string &expected) {
  // Levenshtein distance
  size_t m = actual.length();
  size_t n = expected.length();

  std::vector<size_t> previousRow(n + 1, 0);
  std::vector<size_t> currentRow(n + 1, 0);

  for (size_t j = 0; j <= n; ++j) {
    previousRow[j] = j;
  }

  for (size_t i = 1; i <= m; ++i) {
    currentRow[0] = i;

    for (size_t j = 1; j <= n; ++j) {
      if (actual[i - 1] == expected[j - 1]) {
        currentRow[j] = previousRow[j - 1];
      } else {
        currentRow[j] =
            1 + std::min(currentRow[j - 1],
                         std::min(previousRow[j], previousRow[j - 1]));
      }
    }
    previousRow = currentRow;
  }

  return currentRow[n];
}
