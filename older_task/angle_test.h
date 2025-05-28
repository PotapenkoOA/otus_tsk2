#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::Throw;


#include "angle.h"

TEST(AngleClassTest, test1)
{
    Angle a(12,23); 
    Angle b(12,23); 
    
    ASSERT_TRUE( a == b );
}

TEST(AngleClassTest, test2)
{
    Angle a(12,23); 
    Angle b(2,23); 
    
    ASSERT_FALSE( a == b );
}

TEST(AngleClassTest, test3)
{
    Angle a(12,23); 
    Angle b = a; 
    
    ASSERT_TRUE( a == b );

    Angle c =  a + b;
    
    ASSERT_TRUE( c == Angle(1,23) );

    ASSERT_TRUE( c > Angle(0,23) );

    ASSERT_TRUE( c < Angle(21,23) );
}

bool test(Angle a)
{
    if(a == Angle(1,23))
    return true;
    
    return false;
}

TEST(AngleClassTest, test5)
{
    Angle a(12,23); 
    Angle b = a; 

    Angle c =  a + b;
    
    ASSERT_TRUE( test( c) );
}