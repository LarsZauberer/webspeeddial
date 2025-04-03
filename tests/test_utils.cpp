#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "MockClass.h"
#include "webspeeddial/config.h"
#include "webspeeddial/utils.h"

TEST(find_bookmark, normal_case) {
    std::vector<core::Bookmark> arr = {{"some", "asdf"}, {"hello", "world"}};

    std::string key1 = "some";
    std::string key2 = "hello";
    std::string key3 = "world";
    core::Bookmark *res1 = core::find_bookmark(key1, arr); 
    core::Bookmark *res2 = core::find_bookmark(key2, arr); 
    core::Bookmark *res3 = core::find_bookmark(key3, arr); 

    ASSERT_NE(res1, nullptr);
    ASSERT_EQ(res1->name, arr[0].name);
    ASSERT_EQ(res1->link, arr[0].link);

    ASSERT_NE(res2, nullptr);
    ASSERT_EQ(res2->name, arr[1].name);
    ASSERT_EQ(res2->link, arr[1].link);

    ASSERT_EQ(res3, nullptr);
}

TEST(unalloc_all, normal_case) {
    MockClass *mc = new MockClass();
    MockClass *mc2 = new MockClass();

    EXPECT_CALL(*mc, foo).Times(0);
    EXPECT_CALL(*mc2, foo).Times(0);

    std::vector<MockClass*> arr = {mc, mc2};

    core::unalloc_all<std::vector<MockClass*>, MockClass>(arr);

    ASSERT_EQ(arr[0], nullptr);
    ASSERT_EQ(arr[1], nullptr);
}

TEST(unalloc_all, null_case) {
    MockClass *mc = new MockClass();
    MockClass *mc2 = nullptr;

    EXPECT_CALL(*mc, foo).Times(0);

    std::vector<MockClass*> arr = {mc, mc2};

    core::unalloc_all<std::vector<MockClass*>, MockClass>(arr);

    ASSERT_EQ(arr[0], nullptr);
    ASSERT_EQ(arr[1], nullptr);
}

TEST(unalloc_all, empty_list) {
    std::vector<MockClass*> arr = {};

    core::unalloc_all<std::vector<MockClass*>, MockClass>(arr);
}
