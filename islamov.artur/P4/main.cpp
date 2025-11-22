#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>

namespace islamov {
  int excludeCFFS(const char* string1, const char* string2, char* res_buffer, size_t buffer_size) noexcept {
    if (string1 == nullptr || string2 == nullptr || res_buffer == nullptr) {
      return -1;
    }
    size_t res_index = 0;
    const char* currentCharPtr = string1;
    while (*currentCharPtr != '\0') {
      bool should_exclude = false;
      const char* searchCharPtr = string2;
      while (*searchCharPtr != '\0') {
        if (*currentCharPtr == *searchCharPtr) {
          should_exclude = true;
          break;
        }
        searchCharPtr = searchCharPtr + 1;
      }
      if (!should_exclude) {
        if (res_index >= buffer_size - 1) {
          return -1;
        }
        res_buffer[res_index] = *currentCharPtr;
        res_index = res_index + 1;
      }
      currentCharPtr = currentCharPtr + 1;
    }
    res_buffer[res_index] = '\0';
    return static_cast<int>(res_index);
  }
  int removeLL(const char* input_string, char* res_buffer, size_t buffer_size) noexcept {
    if (input_string == nullptr || res_buffer == nullptr) {
      return -1;
    }
    size_t res_index = 0;
    const char* currentCharPtr = input_string;
    bool last_was_underscore = false;
    while (*currentCharPtr != '\0') {
      unsigned char current_char = static_cast<unsigned char>(*currentCharPtr);
      if (std::isalpha(current_char)) {
        currentCharPtr++;
        continue;
      }
      if (*currentCharPtr == '_') {
        if (!last_was_underscore) {
          if (res_index >= buffer_size - 1) {
            return -1;
          }
          res_buffer[res_index] = *currentCharPtr;
          res_index = res_index + 1;
          last_was_underscore = true;
        }
      } else {
        if (res_index >= buffer_size - 1) {
          return -1;
        }
        res_buffer[res_index] = *currentCharPtr;
        res_index = res_index + 1;
        last_was_underscore = false;
      }
      currentCharPtr = currentCharPtr + 1;
    }
    res_buffer[res_index] = '\0';
    return static_cast<int>(res_index);
  }
} 

int main() {
  const char* string1 = "AbC_aBc";
  const char* string2 = "2ab_c_1d";
  const char* chars_to_remove = "abc";
  const size_t buffer_size = 100;
  char res_buffer[buffer_size];
  std::cout << "Original: " << string1 << '\n';
  islamov::excludeCFFS(string1, chars_to_remove, res_buffer, buffer_size);
  std::cout << "excludeCFFS: " << res_buffer << '\n';
  std::cout << "Original: " << string2 << '\n';
  islamov::removeLL(string2, res_buffer, buffer_size);
  std::cout << "RemoveLL: " << res_buffer  << '\n';
  return 0;
}
