#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>

namespace islamov {
  char* excludeCFFS(const char* string1, const char* string2, char* res_buffer, size_t buffer_size) noexcept
  {
    if (string1 == nullptr || string2 == nullptr || res_buffer == nullptr) {
      return nullptr;
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
        ++searchCharPtr;
      }
      if (!should_exclude) {
        if (res_index >= buffer_size - 1) {
          return nullptr;
        }
        res_buffer[res_index] = *currentCharPtr;
        ++res_index;
      }
      ++currentCharPtr;
    }
    res_buffer[res_index] = '\0';
    return res_buffer;
  }
  char* removeLL(const char* input_string, char* res_buffer, size_t buffer_size) noexcept
  {
    if (input_string == nullptr || res_buffer == nullptr) {
      return nullptr;
    }
    size_t res_index = 0;
    const char* currentCharPtr = input_string;
    bool last_was_underscore = false;
    while (*currentCharPtr != '\0') {
      unsigned char current_char = static_cast<unsigned char>(*currentCharPtr);
      if (std::isalpha(current_char)) {
      } else if (*currentCharPtr == '_') {
        if (!last_was_underscore) {
          if (res_index >= buffer_size - 1) {
            return nullptr;
          }
          res_buffer[res_index] = *currentCharPtr;
          ++res_index;
          last_was_underscore = true;
        }
      } else {
        if (res_index >= buffer_size - 1) {
          return nullptr;
        }
        res_buffer[res_index] = *currentCharPtr;
        ++res_index;
        last_was_underscore = false;
      }
      ++currentCharPtr;
    }
    res_buffer[res_index] = '\0';
    return res_buffer;
  }
}

int main() {
  char* input_line = nullptr;
  size_t buffer_size = 0;
  std::cout << "Enter string: ";
  ssize_t chars_read = getline(&input_line, &buffer_size, stdin);
  if (chars_read < 0) {
    std::cerr << "Error reading input" << '\n';
    if (input_line != nullptr) {
      std::free(input_line);
    }
    return 1;
  }
  if (chars_read > 0 && input_line[chars_read - 1] == '\n') {
    input_line[chars_read - 1] = '\0';
    --chars_read;
  }
  size_t max_res_size = static_cast<size_t>(chars_read) + 1;
  char* res_buffer = static_cast<char*>(std::malloc(max_res_size));
  if (res_buffer == nullptr) {
    std::cerr << "Memory allocation failed" << '\n';
    std::free(input_line);
    return 1;
  }
  const char* secondString = "abcdefghijklmnopqrstuvwxyz";
  char* result = islamov::excludeCFFS(input_line, secondString, res_buffer, max_res_size);
  if (result == nullptr) {
    std::cerr << "Error in string processing" << '\n';
    std::free(input_line);
    std::free(res_buffer);
    return 1;
  }
  std::cout << result << '\n';
  result = islamov::removeLL(input_line, res_buffer, max_res_size);
  if (result == nullptr) {
    std::cerr << "Error in string processing" << '\n';
    std::free(input_line);
    std::free(res_buffer);
    return 1;
  }
  std::cout << result << '\n';
  std::free(input_line);
  std::free(res_buffer);
  return 0;
}
