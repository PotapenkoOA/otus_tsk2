#ifndef _TASK4_TEST_
#define _TASK4_TEST_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "command.h"
#include "move.h"
#include "rotate.h"
#include "task4.h"

using ::testing::Return;
using ::testing::Throw;
using ::testing::InSequence;

TEST(Task4Tests, checkFuelTest)
{
    int minValue = 5;
    int fuelLevel = 0;

    CheckFuelComamnd cmd(&fuelLevel, minValue);
    EXPECT_ANY_THROW( cmd.Execute() );
    
    fuelLevel = 10;
    EXPECT_NO_THROW( cmd.Execute() );      
}

TEST(Task4Tests, burnFuelTest)
{
    int burnFuelVelocity = 3;
    int fuelLevel = 4;
    
    BurnFuelCommand cmd( &fuelLevel, burnFuelVelocity );

    cmd.Execute();
    ASSERT_EQ( fuelLevel, 1);

    cmd.Execute();
    ASSERT_EQ( fuelLevel, 0);  

    int minValue = 2;
    CheckFuelComamnd cmd2(&fuelLevel, minValue);
    ASSERT_ANY_THROW( cmd2.Execute() );
}

class IMoveCommand: public ICommand
{
    public:
    MOCK_METHOD(void, Execute, (), (override));   
};

TEST(Task4Tests, macroCommandTest)
{
    IMoveCommand mcmd;

    EXPECT_CALL(mcmd, Execute()).WillOnce(Return());

    int fuelLevel = 10;
    CheckFuelComamnd cf_cmd(&fuelLevel);
    BurnFuelCommand bf_cmd(&fuelLevel, 3 );

    ICommand* Array[3];
    Array[0] = &cf_cmd;
    Array[1] = &mcmd;
    Array[2] = &bf_cmd;

    MacroCommand cmd( Array, 3 );    
    ASSERT_NO_THROW( cmd.Execute() );
    
    /// проверить уровень топлива
    ASSERT_EQ( fuelLevel, 7 );

    /// проверить простейшесть команды
    EXPECT_CALL(mcmd, Execute()).WillOnce(Throw (exception()));
    ASSERT_ANY_THROW( cmd.Execute() );
}

// изменение мгновенной скорости 
TEST(Task4Tests, ChangeVelocityCommandTest )
{
    VelocityMock obj;
    ChangeVelocityCommand cmd(&obj, Angle(1,2));

    EXPECT_CALL(obj, get()).WillOnce(Return(Vector2(2,5)));
    EXPECT_CALL(obj, set(Vector2(-2,-5))).WillOnce(Return());
   
    ASSERT_NO_THROW( cmd.Execute() );

    EXPECT_CALL(obj, get()).WillOnce(Return(Vector2(0,0)));
    EXPECT_CALL(obj, set(Vector2(0,0))).WillOnce(Return());
   
    ASSERT_NO_THROW( cmd.Execute() );

    EXPECT_CALL(obj, get()).WillOnce(Throw (exception()));    
    ASSERT_ANY_THROW( cmd.Execute() );

    EXPECT_CALL(obj, get()).WillOnce(Return(Vector2(0,0)));
    EXPECT_CALL(obj, set(Vector2(0,0))).WillOnce(Throw (exception()));    
    ASSERT_ANY_THROW( cmd.Execute() );
}

class IRotateCommand: public ICommand
{
    public:
    MOCK_METHOD(void, Execute, (), (override));   
};


TEST(Task4Tests, secondMacroCommandTest)
{
    IRotateCommand r_cmd;
    EXPECT_CALL(r_cmd, Execute()).WillOnce(Return());

    VelocityMock obj;
    ChangeVelocityCommand cv_cmd(&obj, Angle(1,2));

    EXPECT_CALL(obj, get()).WillOnce(Return(Vector2(2,5)));
    EXPECT_CALL(obj, set(Vector2(-2,-5))).WillOnce(Return());   

    ICommand* Array[2];
    Array[0] = &r_cmd;
    Array[1] = &cv_cmd;
    
    MacroCommand cmd( Array, 2 );
    ASSERT_NO_THROW( cmd.Execute() );     
}


#endif