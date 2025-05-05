#include <gtest/gtest.h>
#include <gmock/gmock.h>

//#include "angle_test.h"
//#include "vector_test.h"
//#include "command_test.h"
//#include "exception_library_test.h"
//#include "mo_tests.h"
//#include "ro_tests.h"
//#include "command.h"

//#include "task4_test.h"

//#include "TESTS/IoC_scope_test.h"
//#include "TESTS/IoC_adapter_test.h"
#include "TESTS/Endpoint_test.h"

int main(int argc, char* argv[])
{
   ::testing::InitGoogleMock(&argc, argv);
   ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();    
}