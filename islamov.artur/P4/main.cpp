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
    for (const char* src = inputString; *src != '\0'; ++src)
    {
      bool isLatin = ((*src >= 'a' && *src <= 'z') || (*src >= 'A' && *src <= 'Z'));
      if (!isLatin)
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
}
int main()
{
  char* inputLine = nullptr;
  size_t bufferSize = 0;
  ssize_t charsRead = getline(&inputLine, &bufferSize, stdin);
  if (charsRead < 0)
  {
    std::cerr << "Error reading input" << '\n';
    std::free(inputLine);
    return 1;
  }
  if (charsRead > 0 && inputLine[charsRead - 1] == '\n')
  {
    inputLine[charsRead - 1] = '\0';
    --charsRead;
  }
  const size_t maxResSize = static_cast < size_t > (charsRead) + 1;
  char* resBuffer1 = static_cast < char* > (std::malloc(maxResSize));
  char* resBuffer2 = static_cast < char* > (std::malloc(maxResSize));
  if (resBuffer1 == nullptr || resBuffer2 == nullptr)
  {
    std::cerr << "Memory allocation failed" << '\n';
    std::free(inputLine);
    std::free(resBuffer1);
    std::free(resBuffer2);
    return 1;
  }
  char* result1 = islamov::excludeCFFS(inputLine, "abc", resBuffer1, maxResSize);
  char* result2 = islamov::removeLL(inputLine, resBuffer2, maxResSize);
  if (result1 == nullptr || result2 == nullptr)
  {
    std::cerr << "Error in string processing" << '\n';
    std::free(inputLine);
    std::free(resBuffer1);
    std::free(resBuffer2);
    return 1;
  }
  std::cout << result1 << '\n';
  std::cout << result2 << '\n';
  std::free(inputLine);
  std::free(resBuffer1);
  std::free(resBuffer2);
  return 0;
}
