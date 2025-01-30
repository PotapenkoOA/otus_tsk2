#include "starship.h"
#include "move.h"

TEST(Spacecship_test, test1)
{
 //   vector<double> startLocation = {12,5};
 //   vector<double> constVelocity = {-7,3};
 //   IMove *pMove = new Move();
 //   SpaceShip sokol(pMove,startLocation, constVelocity);
  //  sokol.move();
    
  //  vector<double> newLocation = sokol.getLocation();  
 //   ASSERT_DOUBLE_EQ(5.0, newLocation[0]);
//ASSERT_DOUBLE_EQ(8.0, newLocation[1]);

 //   delete pMove;
}

TEST(Spacecship_test, undefined_location)
{
    MockMove move =   MockMove();
   
    EXPECT_CALL(move, getLocation()).Times(1).WillOnce(::testing::Throw(std::exception()));  
}

TEST(Spacecship_test, undefined_velocity)
{
    MockMove move =   MockMove();
   
    EXPECT_CALL(move, getVelocity()).Times(1).WillOnce(::testing::Throw(std::exception()));  
}

TEST(Spacecship_test, undefined_move)
{
    MockMove move =   MockMove();
    vector<double> startLocation = {12,5};
    
    EXPECT_CALL(move, setLocation(startLocation))
    .Times(1)
    .WillOnce(::testing::Throw(std::exception()));  
}

int main(int argc, char* argv[])
{
    //::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();

    return 1;
}