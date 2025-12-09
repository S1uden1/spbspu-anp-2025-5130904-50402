#include <iostream>
#include <cstring>
#include <cstdlib>
namespace islamov
{
  char* excludeCFFS(const char* string1, const char* string2, char* resBuffer, size_t bufferSize) noexcept
  {
    if (string1 == nullptr || string2 == nullptr || resBuffer == nullptr || bufferSize == 0)
    {
      return nullptr;
    }
    size_t resIndex = 0;
    for (const char* src = string1; *src != '\0'; ++src)
    {
      bool shouldExclude = false;
      for (const char* search = string2; *search != '\0'; ++search)
      {
        if (*src == *search)
        {
          shouldExclude = true;
          break;
        }
      }
      if (!shouldExclude)
      {
        if (resIndex >= bufferSize - 1)
        {
          return nullptr;
        }
        resBuffer[resIndex] = *src;
        ++resIndex;
      }
    }
    resBuffer[resIndex] = '\0';
    return resBuffer;
  }
  char* removeLL(const char* inputString, char* resBuffer, size_t bufferSize) noexcept
  {
    if (inputString == nullptr || resBuffer == nullptr || bufferSize == 0)
    {
      return nullptr;
    }
    size_t resIndex = 0;
    bool lastWasUnderscore = false;
    for (const char* src = inputString; *src != '\0'; ++src)
    {
      if (*src == '_')
      {
        if (!lastWasUnderscore)
        {
          if (resIndex >= bufferSize - 1)
          {
            return nullptr;
          }
          resBuffer[resIndex] = *src;
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
        resBuffer[resIndex] = *src;
        ++resIndex;
        lastWasUnderscore = false;
      }
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
