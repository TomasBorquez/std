#include "../base/base.h"

// Must enable -DRUN_TESTS=ON on the profile to run
static Arena arena;
static StrVector *vec;

void setUp(void) {
  arena = ArenaInit(80800);
}

void tearDown(void) {
  arena.Free(&arena);
}

void testPushShiftUnshift(void) {
  vec = sVec.New();

  String str1 = str.New(&arena, "first");
  String str2 = str.New(&arena, "second");
  String str3 = str.New(&arena, "third");

  sVec.Push(vec, &str1);
  sVec.Push(vec, &str2);
  sVec.Push(vec, &str3);

  // Test Shift
  String shifted = sVec.Shift(vec);
  ASSERT_EQUAL(1, str.Equal(&shifted, &str1));
  ASSERT_EQUAL(2, vec->length);
  ASSERT_EQUAL(1, str.Equal(sVec.At(vec, 0), &str2));

  // Test Unshift
  String str4 = str.New(&arena, "new_first");
  sVec.Unshift(vec, &str4);
  ASSERT_EQUAL(1, str.Equal(sVec.At(vec, 0), &str4));
  ASSERT_EQUAL(3, vec->length);
  ASSERT_EQUAL(1, str.Equal(sVec.At(vec, 1), &str2));

  sVec.Free(vec);
}

void testInsertOperations(void) {
  vec = sVec.New();

  String str1 = str.New(&arena, "first");
  String str2 = str.New(&arena, "second");
  sVec.Push(vec, &str1);
  sVec.Push(vec, &str2);

  // Test Insert in middle
  String str5 = str.New(&arena, "middle");
  sVec.Insert(vec, 1, &str5);
  ASSERT_EQUAL(1, str.Equal(sVec.At(vec, 0), &str1));
  ASSERT_EQUAL(1, str.Equal(sVec.At(vec, 1), &str5));
  ASSERT_EQUAL(1, str.Equal(sVec.At(vec, 2), &str2));
  ASSERT_EQUAL(3, vec->length);

  // Test Insert at beginning
  String str6 = str.New(&arena, "new_start");
  sVec.Insert(vec, 0, &str6);
  ASSERT_EQUAL(1, str.Equal(sVec.At(vec, 0), &str6));
  ASSERT_EQUAL(4, vec->length);

  // Test Insert at end
  String str7 = str.New(&arena, "new_end");
  sVec.Insert(vec, vec->length, &str7);
  ASSERT_EQUAL(1, str.Equal(sVec.At(vec, vec->length - 1), &str7));
  ASSERT_EQUAL(5, vec->length);

  sVec.Free(vec);
}

void testStringSplit(void) {
  vec = sVec.New();

  String testString = str.New(&arena, "hello, how, are, you?");
  String delimiter = str.New(&arena, ", ");
  StrVector *result = str.Split(&arena, &testString, &delimiter);

  ASSERT_EQUAL(4, result->length);
  ASSERT_EQUAL(0, strcmp("hello", sVec.At(result, 0)->data));
  ASSERT_EQUAL(0, strcmp("how", sVec.At(result, 1)->data));
  ASSERT_EQUAL(0, strcmp("are", sVec.At(result, 2)->data));
  ASSERT_EQUAL(0, strcmp("you?", sVec.At(result, 3)->data));

  sVec.Free(result);
}

void testStringCopyAndEqual(void) {
  String str1 = str.New(&arena, "123321");
  String str2 = str.New(&arena, "123321");
  ASSERT_EQUAL(1, str.Equal(&str1, &str2));

  String str3 = str.New(&arena, "different");
  str.Copy(&str3, &str1);
  ASSERT_EQUAL(1, str.Equal(&str1, &str3));

  str2 = str.New(&arena, "123333");
  ASSERT_EQUAL(0, str.Equal(&str1, &str2));
  str1 = str.New(&arena, "123");
  str2 = str.New(&arena, "1234");
  ASSERT_EQUAL(0, str.Equal(&str1, &str2));

  str.Copy(&str2, &str1);
  ASSERT_EQUAL(1, str.Equal(&str1, &str2));
}

void testStringConcat(void) {
  String str1 = str.New(&arena, "123");
  String str2 = str.New(&arena, "321");
  String result = str.Concat(&arena, &str1, &str2);
  String expected = str.New(&arena, "123321");

  ASSERT_EQUAL(1, str.Equal(&result, &expected));
  ASSERT_EQUAL(6, result.length);
}

void testStringTrim(void) {
  struct {
    char *input;
    char *expected;
  } test_cases[] = {
        {" ", ""},
        {" test", "test"},
        {" test ", "test"},
        {"  ", ""},
        {" test   ", "test"},
        {"   te12st  ", "te12st"},
        {"   te12st  123 ", "te12st  123"},
        {"   te12st  123 3", "te12st  123 3"}
      };

  for (size i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
    String str1 = str.New(&arena, test_cases[i].input);
    String expected = str.New(&arena, test_cases[i].expected);
    str.Trim(&str1);
    ASSERT_EQUAL(1, str.Equal(&str1, &expected));
  }
}

void testStringCase(void) {
  struct {
    char *input;
    char *expectedUpper;
    char *expectedLower;
  } test_cases[] = {
        // Basic cases
        {"test", "TEST", "test"},
        {"TEST", "TEST", "test"},
        {"Test", "TEST", "test"},

        // Mixed case
        {"TeStInG123", "TESTING123", "testing123"},
        {"HELLO world", "HELLO WORLD", "hello world"},

        // Numbers and special characters
        {"123ABC!@#", "123ABC!@#", "123abc!@#"},
        {"Te12St!@", "TE12ST!@", "te12st!@"},

        // Spaces and empty strings
        {"", "", ""},
        {" ", " ", " "},
        {"  Test  ", "  TEST  ", "  test  "},

        // Edge cases
        {"A", "A", "a"},
        {"z", "Z", "z"},
        {"Test Test", "TEST TEST", "test test"},
        {"TeSt@123 TEST", "TEST@123 TEST", "test@123 test"}
      };

  for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
    // Test ToUpper
    String str1 = str.New(&arena, test_cases[i].input);
    String expectedUpper = str.New(&arena, test_cases[i].expectedUpper);
    str.ToUpper(&str1);
    ASSERT_EQUAL(1, str.Equal(&str1, &expectedUpper));

    // Test ToLower (using fresh string since str1 was modified)
    String str2 = str.New(&arena, test_cases[i].input);
    String expectedLower = str.New(&arena, test_cases[i].expectedLower);
    str.ToLower(&str2);
    ASSERT_EQUAL(1, str.Equal(&str2, &expectedLower));
  }
}

void testStringSlice(void) {
  struct {
    char *input;
    i32 start;
    i32 end;
    char *expected;
  } test_cases[] = {
        {"12345", 0, -1, "1234"},
        {"12345", 2, 5, "345"},
        {"12345", 0, 1, "1"},
        {"12345", 1, -1, "234"},
        {"1234", 0, 3, "123"}
      };

  for (size i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
    String str1 = str.New(&arena, test_cases[i].input);
    String expected = str.New(&arena, test_cases[i].expected);
    str.Slice(&str1, test_cases[i].start, test_cases[i].end);
    ASSERT_EQUAL(1, str.Equal(&str1, &expected));
  }
}

void testTimeNowAndWaitTime(void) {
  i64 startTime = Now();
  WaitTime(1000);
  i64 currTime = Now();
  i64 result = currTime - startTime;
  ASSERT_EQUAL(1, result >= 1000 && result <= 1050);
}

int main(void) {
  UNITY_BEGIN();
  // Start
  {
    setUp();
    RUN_TEST(testPushShiftUnshift);
    RUN_TEST(testInsertOperations);
    RUN_TEST(testStringSplit);
    RUN_TEST(testStringCopyAndEqual);
    RUN_TEST(testStringConcat);
    RUN_TEST(testStringCase);
    RUN_TEST(testStringTrim);
    RUN_TEST(testStringSlice);
    RUN_TEST(testTimeNowAndWaitTime);
    tearDown();
  }
  UNITY_END();
}
