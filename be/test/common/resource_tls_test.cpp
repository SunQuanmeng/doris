// Copyright (c) 2017, Baidu.com, Inc. All Rights Reserved

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "common/resource_tls.h"

#include <gtest/gtest.h>

#include "gen_cpp/Types_types.h"
#include "util/logging.h"

namespace palo {

class ResourceTlsTest : public testing::Test {
};

TEST_F(ResourceTlsTest, EmptyTest) {
    ASSERT_TRUE(ResourceTls::get_resource_tls() == nullptr);
    ASSERT_TRUE(ResourceTls::set_resource_tls((TResourceInfo*)1) != 0);
}

TEST_F(ResourceTlsTest, NormalTest) {
    ResourceTls::init();
    ASSERT_TRUE(ResourceTls::get_resource_tls() == nullptr);
    TResourceInfo *info = new TResourceInfo();
    info->user = "testUser";
    info->group = "testGroup";
    ASSERT_TRUE(ResourceTls::set_resource_tls(info) == 0);
    TResourceInfo *getInfo = ResourceTls::get_resource_tls();
    ASSERT_STREQ("testUser", getInfo->user.c_str());
    ASSERT_STREQ("testGroup", getInfo->group.c_str());
}

}

int main(int argc, char** argv) {
    std::string conffile = std::string(getenv("DORIS_HOME")) + "/conf/be.conf";
    if (!palo::config::init(conffile.c_str(), false)) {
        fprintf(stderr, "error read config file. \n");
        return -1;
    }
    palo::init_glog("be-test");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
