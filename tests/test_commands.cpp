#include <gtest/gtest.h>
#include "webspeeddial/commands.h"
#include "webspeeddial/Runner.h"
#include "MockRunner.h"

using namespace core;

TEST(copy_content_from_file, null_test) {
  FILE *f = NULL;
  std::string *out = copy_content_from_file(f);
  ASSERT_TRUE(out == NULL);
}

TEST(copy_content_from_file, normal_case) {
  std::string test_str = std::string("hello world!");
  FILE *f = fmemopen(test_str.data(), test_str.size(), "r");
  std::string *result = copy_content_from_file(f);

  ASSERT_EQ(*result, "hello world!");
  delete result;
}

TEST(run_cmd, real_runner) {
  std::string cmd = "echo 'Hello World!'";
  Runner r(&cmd);
  std::string *out = run_cmd(&r);
  ASSERT_TRUE(out != NULL);
  ASSERT_EQ(*out, "Hello World!\n");
  delete out;
}

TEST(run_cmd, mock_runner) {
  std::string data = "This is some data!";
  FILE *f = fmemopen(data.data(), data.size(), "r");

  MockRunner r;
  EXPECT_CALL(r, run()).Times(1).WillRepeatedly(testing::Return(f));
  EXPECT_CALL(r, close()).Times(1);

  std::string *out = run_cmd(&r);

  ASSERT_TRUE(out != NULL);
  ASSERT_EQ(*out, data);
  delete out;
}
