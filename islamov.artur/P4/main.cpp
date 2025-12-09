#include <iostream>
#include <cstring>
#include <cstdlib>
namespace islamov
{
  char* excludeCFFS(const char* string1, const char* string2, char* resBuffer, size_t bufferSize) noexcept
  {
    if (string1 == nullptr || string2 == nullptr || resBuffer == nullptr)
    {
      return nullptr;
    }
    size_t resIndex = 0;
    const char* currentCharPtr = string1;
    while (*currentCharPtr != '\0')
    {
      bool shouldExclude = false;
      const char* searchCharPtr = string2;
      while (*searchCharPtr != '\0')
      {
        if (*currentCharPtr == *searchCharPtr)
        {
          shouldExclude = true;
          break;
        }
        ++searchCharPtr;
      }
      if (!shouldExclude)
      {
        if (resIndex >= bufferSize - 1)
        {
          return nullptr;
        }
        resBuffer[resIndex] = *currentCharPtr;
        ++resIndex;
      }
      ++currentCharPtr;
    }
    resBuffer[resIndex] = '\0';
    return resBuffer;
  }
  char* removeLL(const char* inputString, char* resBuffer, size_t bufferSize) noexcept
  {
    if (inputString == nullptr || resBuffer == nullptr)
    {
      return nullptr;
    }
    size_t resIndex = 0;
    const char* currentCharPtr = inputString;
    bool lastWasUnderscore = false;
    while (*currentCharPtr != '\0')
    {
      if (*currentCharPtr == '_')
      {
        if (!lastWasUnderscore)
        {
          if (resIndex >= bufferSize - 1)
          {
            return nullptr;
          }
          resBuffer[resIndex] = *currentCharPtr;
          ++resIndex;
          lastWasUnderscore = true;
        }
      }
      else
      {
        if (resIndex >= bufferSize - 1)
        {
          return nullptr;
        }
        resBuffer[resIndex] = *currentCharPtr;
        ++resIndex;
        lastWasUnderscore = false;
      }
      ++currentCharPtr;
    }
    resBuffer[resIndex] = '\0';
    return resBuffer;
  }
}
int main()
{
  char* inputLine = nullptr;
  size_t bufferSize = 0;
  std::cout << "Enter string: ";
  ssize_t charsRead = getline(&inputLine, &bufferSize, stdin);
  if (charsRead < 0)
  {
    std::cerr << "Error reading input" << '\n';
    if (inputLine != nullptr)
    {
      std::free(inputLine);
    }
    return 1;
  }
  if (charsRead > 0 && inputLine[charsRead - 1] == '\n')
  {
    inputLine[charsRead - 1] = '\0';
    --charsRead;
  }
  size_t maxResSize = static_cast < size_t > (charsRead) + 1;
  char* resBuffer = static_cast < char* > (std::malloc(maxResSize));
  if (resBuffer == nullptr)
  {
    std::cerr << "Memory allocation failed" << '\n';
    std::free(inputLine);
    return 1;
  }
  const char* secondString = "abc";
  char* result = islamov::excludeCFFS(inputLine, secondString, resBuffer, maxResSize);
  if (result == nullptr)
  {
    std::cerr << "Error in string processing" << '\n';
    std::free(inputLine);
    std::free(resBuffer);
    return 1;
  }
  std::cout << result << '\n';
  result = islamov::removeLL(inputLine, resBuffer, maxResSize);
  if (result == nullptr)
  {
    std::cerr << "Error in string processing" << '\n';
    std::free(inputLine);
    std::free(resBuffer);
    return 1;
  }
  std::cout << result << '\n';
  std::free(inputLine);
  std::free(resBuffer);
  return 0;
}
