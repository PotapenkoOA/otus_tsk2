#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::Throw;

#include "vector2.h"

TEST(VectorClassTest, test1)
{
    Vector2 a(12,23); 
    Vector2 b(12,23); 
    
    ASSERT_TRUE( a == b );

    Vector2 c = b;

    ASSERT_TRUE( c == b );
}

TEST(VectorClassTest, test2)
{
    Vector2 a(12,23); 
    Vector2 b(12,23); 
    
    ASSERT_EQ( a + b, Vector2(24, 46) );
}

#include "angle.h"
//Vector2 v= pObject->get()*m_a;
TEST(VectorClassTest, test3)
{
    Vector2 a(12,23); 
    Angle b(1,2); 
    
    ASSERT_EQ( a.rotate( b ), Vector2(-12, -23) );
}