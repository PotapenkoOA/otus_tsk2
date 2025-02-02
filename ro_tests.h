#ifndef RO_TESTS
#define RO_TESTS

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "rotatingobject.h"
#include "rotate.h"

using ::testing::Return;
using ::testing::Throw;
using ::testing::_;
using ::testing::DoAll;

TEST(RotatingSpacecshipTest, test1)
{
    RotatingMock bundle; 
    Rotate rotate(&bundle);  

    EXPECT_CALL(bundle, getAngle()).WillOnce(Return(Angle(2,5)));
    EXPECT_CALL(bundle, getAngularVelocity()).WillOnce(Return(Angle(3,5)));

   // EXPECT_CALL(bundle, setAngle).WillOnce(DoAll(SaveArg<0>(&actual_array)));
   // EXPECT_THAT(actual_array, Angle(1,5));

   EXPECT_CALL(bundle, setAngle(Angle(0,5)));
          
    rotate.Execute();

} 
/*
TEST(RotatingSpacecshipTest, undefined_location)
{
    RotatingMock sokol; 
    Rotate rotate(&sokol);  

    EXPECT_CALL(sokol, getAngle()).WillOnce(Return(Angle(12,5)));
    EXPECT_CALL(sokol, getAngularVelocity()).WillOnce(Return(Angle(-7,3)));

   EXPECT_CALL(sokol, setAngle(Angle(5,8))).WillOnce(Return());
          
    EXPECT_ANY_THROW(rotate.Execute());
}

TEST(RotatingSpacecshipTest, undefined_velocity)
{
    RotatingMock sokol; 
    Rotate rotate(&sokol);  

    EXPECT_CALL(sokol, getAngle()).WillOnce(Return(Angle(12,5)));
    EXPECT_CALL(sokol, getAngularVelocity()).WillOnce(Return(Angle(-7,3)));

    EXPECT_CALL(sokol, setAngle(Angle(5,8))).WillOnce(Return());
          
    EXPECT_ANY_THROW(rotate.Execute());  
}
using ::testing::_;
TEST(RotatingSpacecshipTest, undefined_move)
{
    RotatingMock sokol; 
    Rotate rotate(&sokol); 

    EXPECT_CALL(sokol, getAngle()).WillOnce(Return(Angle(12,5)));
    EXPECT_CALL(sokol, getAngularVelocity()).WillOnce(Return(Angle(-7,3)));

    EXPECT_CALL(sokol, setAngle(Angle(5,8))).WillOnce(Return());
          
    EXPECT_ANY_THROW (rotate.Execute());  
}
*/
#endif