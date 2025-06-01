#ifndef MO_TESTS
#define MO_TESTS

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "movingobject.h"
#include "move.h"

using ::testing::Return;
using ::testing::Throw;
using ::testing::InSequence;

TEST(MovingSpacecshipTest, test1)
{
    MovingMock sokol; 
    Move move(&sokol);  

    EXPECT_CALL(sokol, getLocation()).WillOnce(Return(Vector2(12,5)));
    EXPECT_CALL(sokol, getVelocity()).WillOnce(Return(Vector2(-7,3)));

    EXPECT_CALL(sokol, setLocation(Vector2(5,8))).WillOnce(Return());
          
    move.Execute();
}

TEST(MovingSpacecshipTest, undefined_location)
{
    MovingMock sokol; 
    Move move(&sokol);  

    ON_CALL(sokol, getLocation()).WillByDefault(Throw(std::exception()));
    ON_CALL(sokol, getVelocity()).WillByDefault(Return(Vector2{-7,3}));

    EXPECT_CALL(sokol, getLocation()).Times(::testing::AnyNumber());
    EXPECT_CALL(sokol, getVelocity()).Times(::testing::AnyNumber());
         
    EXPECT_ANY_THROW(move.Execute());
}

TEST(MovingSpacecshipTest, undefined_velocity)
{
    MovingMock sokol; 
    Move move(&sokol);  

    ON_CALL(sokol, getLocation()).WillByDefault(Return(Vector2{-7,3}));
    ON_CALL(sokol, getVelocity()).WillByDefault(Throw(std::exception()));

    EXPECT_CALL(sokol, getLocation()).Times(::testing::AnyNumber());
    EXPECT_CALL(sokol, getVelocity()).Times(::testing::AnyNumber());
         
    EXPECT_ANY_THROW(move.Execute());
}

TEST(MovingSpacecshipTest, undefined_move)
{
    MovingMock sokol; 
    Move move(&sokol);  

    ON_CALL(sokol, getLocation()).WillByDefault(Return(Vector2{12,5}));
    ON_CALL(sokol, getVelocity()).WillByDefault(Return(Vector2{-7,3}));

    EXPECT_CALL(sokol, getLocation()).Times(::testing::AnyNumber());
    EXPECT_CALL(sokol, getVelocity()).Times(::testing::AnyNumber());

    EXPECT_CALL(sokol, setLocation(::testing::A<Vector2>())).WillOnce(Throw(std::exception()));
         
    EXPECT_ANY_THROW(move.Execute()); 
}

#endif