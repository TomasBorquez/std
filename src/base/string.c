#include "string.h"

static size maxStringSize = 10000;

bool strIsNull(String *str) {
  return str == NULL || str->length == 0 || str->data == NULL;
}

static size strLength(char *str, size maxSize) {
  ASSERT(str != NULL, "string should never be NULL");

  size len = 0;
  while (len < maxSize && str[len] != '\0') {
    len++;
  }

  return len;
}

static void setMaxStrSize(size size) {
  maxStringSize = size;
}

static void addNullTerminator(char *str, size len) {
  str[len] = '\0';
}

static String strNewSize(Arena *arena, char *str, size len) {
  const size memorySize = sizeof(char) * len + 1; // * Includes null terminator
  char *allocatedString = arena->Alloc(arena, memorySize);

  memcpy(allocatedString, str, memorySize);
  addNullTerminator(allocatedString, len);
  return (String){len, allocatedString};
}

static String strNew(Arena *arena, char *str) {
  const size len = strLength(str, maxStringSize);
  const size memorySize = sizeof(char) * len + 1; // * Includes null terminator
  char *allocatedString = arena->Alloc(arena, memorySize);

  memcpy(allocatedString, str, memorySize);
  addNullTerminator(allocatedString, len);
  return (String){len, allocatedString};
}

static String strConcat(Arena *arena, String *string1, String *string2) {
  ASSERT(!strIsNull(string1), "string1 should never be NULL");
  ASSERT(!strIsNull(string2), "string2 should never be NULL");

  const size len = string1->length + string2->length;
  const size memorySize = sizeof(char) * len + 1; // * Includes null terminator
  char *allocatedString = arena->Alloc(arena, memorySize);

  memcpy_s(allocatedString, memorySize, string1->data, string1->length);
  memcpy_s(allocatedString + string1->length, memorySize, string2->data, string2->length);
  addNullTerminator(allocatedString, len);
  return (String){len, allocatedString};
};

static void strCopy(String *destination, String *source) {
  ASSERT(!strIsNull(destination), "destination should never be NULL");
  ASSERT(!strIsNull(source), "source should never be NULL");
  ASSERT(destination->length >= source->length, "destination length should never smaller than source length");

  const errno_t result = memcpy_s(destination->data, destination->length, source->data, source->length);

  ASSERT(result == 0, "result should never be anything but 0");
  destination->length = source->length;
  addNullTerminator(destination->data, destination->length);
}

static bool strEqual(String *string1, String *string2) {
  if (string1->length != string2->length) {
    return false;
  }

  if (memcmp(string1->data, string2->data, string1->length) != 0) {
    return false;
  }
  return true;
}

static StrVector *strSplit(Arena *arena, String *str, String *delimiter) {
  ASSERT(!strIsNull(str), "str should never be NULL");
  ASSERT(!strIsNull(delimiter), "delimiter should never be NULL");

  char *start = str->data;
  const char *end = str->data + str->length;
  char *curr = start;
  StrVector *result = sVec.New();
  if (delimiter->length == 0) {
    for (size i = 0; i < str->length; i++) {
      String currString = strNewSize(arena, str->data + i, 1);
      sVec.Push(result, &currString);
    }
    return result;
  }

  while (curr < end) {
    char *match = NULL;
    for (char *search = curr; search <= end - delimiter->length; search++) {
      if (memcmp(search, delimiter->data, delimiter->length) == 0) {
        match = search;
        break;
      }
    }

    if (!match) {
      String currString = strNewSize(arena, curr, end - curr);
      sVec.Push(result, &currString);
      break;
    }

    size len = match - curr;
    String currString = strNewSize(arena, curr, len);
    sVec.Push(result, &currString);

    curr = match + delimiter->length;
  }

  return result;
}

void strToUpper(String *str) {
  for (int i = 0; i < str->length; ++i) {
    char currChar = str->data[i];
    str->data[i] = toupper(currChar);
  }
}

void strToLower(String *str) {
  for (int i = 0; i < str->length; ++i) {
    char currChar = str->data[i];
    str->data[i] = tolower(currChar);
  }
}

bool isSpace(char character) {
  return character == ' ' || character == '\n' || character == '\t' || character == '\r';
}

void strTrim(String *str) {
  char *firstChar = NULL;
  char *lastChar = NULL;
  if (str->length == 0) {
    return;
  }

  if (str->length == 1) {
    if (isSpace(str->data[0])) {
      str->data[0] = '\0';
      str->length = 0;
    }
    return;
  }

  for (int i = 0; i < str->length; ++i) {
    char *currChar = &str->data[i];
    if (isSpace(*currChar)) {
      continue;
    }

    if (firstChar == NULL) {
      firstChar = currChar;
    }
    lastChar = currChar;
  }

  if (firstChar == NULL || lastChar == NULL) {
    str->data[0] = '\0';
    str->length = 0;
    addNullTerminator(str->data, 0);
    return;
  }

  size len = (lastChar - firstChar) + 1;
  memcpy_s(str->data, str->length, firstChar, len);
  str->length = len;
  addNullTerminator(str->data, len);
}

void strSlice(String *str, i32 start, i32 end) {
  ASSERT(start >= 0, "start index must be non-negative");
  ASSERT(start <= str->length, "start index out of bounds");
  if (end < 0) {
    end = str->length + end;
  }
  ASSERT(end >= start, "end must be greater than or equal to start");
  ASSERT(end <= str->length, "end index out of bounds");

  char *strStart = str->data + start;
  char *strEnd = &str->data[end];
  memcpy_s(str->data, str->length, strStart, strEnd - strStart);
  size len = end - start;
  str->length = len;
  addNullTerminator(str->data, str->length);
}

StrVT str = {
  .SetMaxSize = setMaxStrSize,
  .New = strNew,
  .Copy = strCopy,
  .Split = strSplit,
  .Equal = strEqual,
  .Concat = strConcat,
  .ToUpper = strToUpper,
  .ToLower = strToLower,
  .IsNull = strIsNull,
  .Trim = strTrim,
  .Slice = strSlice,
};
