#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include <optional>
#include <string>
#include <vector>
#include "MockClass.h"
#include "MockRunner.h"
#include "webspeeddial/CMD_File.h"
#include "webspeeddial/CMD_Runner.h"
#include "webspeeddial/config.h"
#include "webspeeddial/utils.h"

TEST(find_bookmark, normal_case) {
    core::Bookmark bm1 = {"some", "asdf"};
    core::Bookmark bm2 = {"hello", "world"};

    std::vector<core::Bookmark> arr;
    arr.reserve(2); 
    arr.push_back(std::move(bm1));
    arr.push_back(std::move(bm2));

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

TEST(run_cmd, normal_case) {
    std::string cmd = "mycommand";
    std::string inp = "";

    std::string output = "asdf";

    MockRunner r;
    MockFile file(output);
    std::optional<MockFile> f = {std::move(file)};

    EXPECT_CALL(r, run(cmd, inp)).Times(1).WillOnce(testing::Return(f));

    std::optional<std::string> out = core::run_cmd<MockRunner, MockFile>(r, cmd, inp); 
    ASSERT_TRUE(out.has_value());
    ASSERT_EQ(out.value(), output);
}

TEST(run_cmd, real_world) {
    std::string cmd = "echo 'hello world'";
    std::string inp = "";

    core::CMD_Runner r;
    std::optional<std::string> out = core::run_cmd<core::CMD_Runner, core::CMD_File>(r, cmd, inp);
    ASSERT_TRUE(out.has_value());
    ASSERT_EQ(out.value(), "hello world\n");
}
