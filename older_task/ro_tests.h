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

TEST(RotatingSpacecshipTest, test_1)
{
    RotatingMock bundle; 
    Rotate rotate(&bundle);  

    EXPECT_CALL(bundle,           getAngle()).WillOnce(Return(Angle(2,5)));
    EXPECT_CALL(bundle, getAngularVelocity()).WillOnce(Return(Angle(3,5)));

    EXPECT_CALL(bundle, setAngle(Angle(0,5)));
          
    rotate.Execute();

} 

TEST(RotatingSpacecshipTest, undefined_angle)
{
    RotatingMock bundle; 
    Rotate rotate(&bundle);  

    ON_CALL(bundle, getAngle()).WillByDefault(Return(Angle(2,5)));
    ON_CALL(bundle, getAngularVelocity()).WillByDefault(Throw(std::exception()));

    EXPECT_CALL(bundle, getAngle()).Times(::testing::AnyNumber());
    EXPECT_CALL(bundle, getAngularVelocity()).Times(::testing::AnyNumber());
         
    EXPECT_ANY_THROW(rotate.Execute());

} 

TEST(RotatingSpacecshipTest, undefined_anglularvelocity)
{
    RotatingMock bundle; 
    Rotate rotate(&bundle);  

    ON_CALL(bundle, getAngle()).WillByDefault(Throw(std::exception()));
    ON_CALL(bundle, getAngularVelocity()).WillByDefault(Return(Angle(2,5)));

    EXPECT_CALL(bundle, getAngle()).Times(::testing::AnyNumber());
    EXPECT_CALL(bundle, getAngularVelocity()).Times(::testing::AnyNumber());
         
    EXPECT_ANY_THROW(rotate.Execute());

} 

TEST(RotatingSpacecshipTest, undefined_newangle)
{
    RotatingMock bundle; 
    Rotate rotate(&bundle);  

    ON_CALL(bundle, getAngle()).WillByDefault(Return(Angle(2,5)));
    ON_CALL(bundle, getAngularVelocity()).WillByDefault(Return(Angle(3,5)));

    EXPECT_CALL(bundle, getAngle()).Times(::testing::AnyNumber());
    EXPECT_CALL(bundle, getAngularVelocity()).Times(::testing::AnyNumber());

    EXPECT_CALL(bundle, setAngle(::testing::A<Angle>())).WillOnce(Throw(std::exception()));
         
    EXPECT_ANY_THROW(rotate.Execute());

} 

#endif