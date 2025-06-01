#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SRV_TESTS.h"

int main(int argc, char* argv[])
{
   ::testing::InitGoogleMock(&argc, argv);
   ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();    
}