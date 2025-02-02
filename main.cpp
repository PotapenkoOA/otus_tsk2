#include <gtest/gtest.h>
#include <gmock/gmock.h>


#include "mo_tests.h"
//#include "ro_tests.h"
//#include "angle_test.h"

int main(int argc, char* argv[])
{
   
   ::testing::InitGoogleMock(&argc, argv);
   ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}