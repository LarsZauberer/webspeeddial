#include "webspeeddial/config.h"
#include "webspeeddial/utils.h"
#include <gtest/gtest.h>

using namespace core;

TEST(bookmarks_to_fzf, null_test) {
  std::vector<BookMark *> *bm = NULL;
  ASSERT_EQ(bookmarks_to_fzf(bm), "");
}

TEST(bookmarks_to_fzf, null_element) {
  BookMark *a = NULL;
  BookMark *b = NULL;

  std::vector<BookMark *> bm = {a, b};
  ASSERT_EQ(bookmarks_to_fzf(&bm), "");
}

TEST(bookmarks_to_fzf, normal_case) {
  BookMark a = {"Hello", "hello"};
  BookMark b = {"World", "world"};

  std::vector<BookMark *> bm = {&a, &b};
  ASSERT_EQ(bookmarks_to_fzf(&bm), "Hello\nWorld");
}

TEST(find_name, null_array) {
  std::vector<BookMark *> *bookmarks = NULL;
  std::string find = "Hello";
  BookMark *out = find_name(&find, bookmarks);
  ASSERT_TRUE(out == NULL);
}

TEST(find_name, null_element) {
  BookMark a = {"Hello", "1"};
  BookMark b = {"World", "2"};
  std::vector<BookMark *> bookmarks = {&a, &b};
  std::string *find = NULL;
  ASSERT_TRUE(find_name(find, &bookmarks) == NULL);
}

TEST(find_name, first_element) {
  BookMark a = {"Hello", "1"};
  BookMark b = {"World", "2"};
  std::vector<BookMark *> bookmarks = {&a, &b};
  std::string find = "Hello";
  ASSERT_EQ(find_name(&find, &bookmarks), &a);
}

TEST(find_name, second_element) {
  BookMark a = {"Hello", "1"};
  BookMark b = {"World", "2"};
  std::vector<BookMark *> bookmarks = {&a, &b};
  std::string find = "World";
  ASSERT_EQ(find_name(&find, &bookmarks), &b);
}

TEST(remove_trailing, null_test) {
  std::string *a = NULL;
  ASSERT_TRUE(remove_trailing(a) == NULL);
}

TEST(remove_trailing, no_backslash) {
  std::string a = "test";
  ASSERT_TRUE(*remove_trailing(&a) == a);
  ASSERT_TRUE(remove_trailing(&a) == &a);
}

TEST(remove_trailing, normal_case) {
  std::string a = "test\n";
  ASSERT_TRUE(*remove_trailing(&a) == "test");
  ASSERT_TRUE(remove_trailing(&a) == &a);
}
