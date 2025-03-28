#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <cstdio>
#define CATCH_CONFIG_MAIN
#include "../src/commands.h"
#include "../src/config.h"
#include "../src/utils.h"
#include <catch2/catch_all.hpp>
#include "../src/Runner.h"
#include "../src/MockRunner.h"

using std::vector;

TEST_CASE("BookMark to Fzf with null", "[bookmarks_to_fzf]") {
  vector<BookMark *> *bookmarks = NULL;
  REQUIRE(bookmarks_to_fzf(bookmarks) == "");
}

TEST_CASE("BookMark to Fzf null element", "[bookmarks_to_fzf]") {
  BookMark *ap = NULL;
  vector<BookMark *> bookmarks = {ap};
  REQUIRE(bookmarks_to_fzf(&bookmarks) == "");
}

TEST_CASE("BookMark to Fzf correct", "[bookmarks_to_fzf]") {
  BookMark a = {"Hello", "1"};
  BookMark b = {"World", "2"};
  vector<BookMark *> bookmarks = {&a, &b};
  REQUIRE(bookmarks_to_fzf(&bookmarks) == "Hello\nWorld");
}

////

TEST_CASE("Find BookMark null array", "[find_name]") {
  vector<BookMark *> *bookmarks = NULL;
  string find = "Hello";
  REQUIRE(find_name(&find, bookmarks) == NULL);
}

TEST_CASE("Find BookMark null element", "[find_name]") {
  BookMark a = {"Hello", "1"};
  BookMark b = {"World", "2"};
  vector<BookMark *> bookmarks = {&a, &b};
  string *find = NULL;
  REQUIRE(find_name(find, &bookmarks) == NULL);
}

TEST_CASE("Find BookMark first_ele", "[find_name]") {
  BookMark a = {"Hello", "1"};
  BookMark b = {"World", "2"};
  vector<BookMark *> bookmarks = {&a, &b};
  string find = "Hello";
  REQUIRE(find_name(&find, &bookmarks) == &a);
}

TEST_CASE("Find BookMark second_ele", "[find_name]") {
  BookMark a = {"Hello", "1"};
  BookMark b = {"World", "2"};
  vector<BookMark *> bookmarks = {&a, &b};
  string find = "World";
  REQUIRE(find_name(&find, &bookmarks) == &b);
}

////

TEST_CASE("Remove Trailing Null", "[remove_trailing]") {
  string *a = NULL;
  REQUIRE(remove_trailing(a) == NULL);
}

TEST_CASE("Remove Trailing No backslash n", "[remove_trailing]") {
  string a = "test";
  REQUIRE(*remove_trailing(&a) == a);
  REQUIRE(remove_trailing(&a) == &a);
}

TEST_CASE("Remove Trailing with backslash n", "[remove_trailing]") {
  string a = "test\n";
  REQUIRE(*remove_trailing(&a) == "test");
  REQUIRE(remove_trailing(&a) == &a);
}

////

TEST_CASE("null", "[copy_content_from_file]") {
  FILE *f = NULL;
  string *out = copy_content_from_file(f);
  REQUIRE(out == NULL);
}

TEST_CASE("hello world value", "[copy_content_from_file]") {
  string test_str = string("hello world!");
  FILE *f = fmemopen(test_str.data(), test_str.size(), "r");
  std::string *result = copy_content_from_file(f);

  REQUIRE(*result == "hello world!");
  delete result;
}

TEST_CASE("echo hello world", "[run_cmd]") {
    string cmd = "echo 'Hello World!'";
    Runner r(&cmd);
    string *out = run_cmd(&r);
    REQUIRE(out != NULL);
    REQUIRE(*out == "Hello World!\n");
    delete out;
}

TEST_CASE("real output", "[run_cmd]") {
    string data = "This is some data!";
    MockRunner r(&data);
    string *out = run_cmd(&r);
    REQUIRE(out != NULL);
    REQUIRE(*out == data);
    delete out;
}
