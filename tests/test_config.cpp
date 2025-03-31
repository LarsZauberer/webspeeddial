#include "MockConfigFile.h"
#include "MockNode.h"
#include "webspeeddial/ConfigManager.h"
#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include <string>

using namespace core;

// TEST(ConfigManager, normal_case) {
//     MockConfigFile mcf;

//     MockNode root;
//     MockNode runner;
//     MockNode bookmarks;

//     // Setup ConfigFile Mock
//     EXPECT_CALL(mcf, read).Times(1).WillOnce(testing::Return(&root));
//     EXPECT_CALL(mcf, file_exists).Times(1).WillOnce(testing::Return(true));

//     // Setup Node Mock
//     EXPECT_CALL(root, get(std::string("Runner"))).WillRepeatedly(testing::Return(&runner));
//     EXPECT_CALL(root, get(std::string("Bookmarks"))).WillRepeatedly(testing::Return(&bookmarks));

//     // EXPECT_CALL(runner, is_defined)

// }

TEST(ConfigManager, no_file) {
    MockConfigFile mcf;

    EXPECT_CALL(mcf, file_exists).Times(1).WillOnce(testing::Return(false));
    EXPECT_CALL(mcf, write).Times(1);

    ConfigManager cm(&mcf);
    mcf.read();
}
