#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <cstdint>

uint32_t factorial( uint32_t number ) {
    return number <= 1 ? number : factorial(number-1) * number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( factorial( 1) == 1 );
    REQUIRE( factorial( 2) == 2 );
    REQUIRE( factorial( 3) == 6 );
    REQUIRE( factorial(10) == 3'628'800 );
}

TEST_CASE("Find BookMark null array", "[find_name]") {
  BookMark **bookmarks = NULL;
  string find = "Hello";
  REQUIRE(find_name(&find, bookmarks, 0) == NULL);
}

TEST_CASE("Find BookMark null element", "[find_name]") {
  BookMark a = {"Hello", "1"};
  BookMark b = {"World", "2"};
  BookMark *bookmarks[] = {&a, &b};
  string *find = NULL;
  REQUIRE(find_name(find, bookmarks, 2) == NULL);
}

TEST_CASE("Find BookMark first_ele", "[find_name]") {
  BookMark a = {"Hello", "1"};
  BookMark b = {"World", "2"};
  BookMark *bookmarks[] = {&a, &b};
  string find = "Hello";
  REQUIRE(find_name(&find, bookmarks, 2) == &a);
}

TEST_CASE("Find BookMark second_ele", "[find_name]") {
  BookMark a = {"Hello", "1"};
  BookMark b = {"World", "2"};
  BookMark *bookmarks[] = {&a, &b};
  string find = "World";
  REQUIRE(find_name(&find, bookmarks, 2) == &b);
}

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
