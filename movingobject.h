#ifndef __MOVINGOBJ
#define __MOVINGOBJ

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
using namespace std;

class IMovingObject{
    public:
       
      virtual vector<int> getLocation() = 0;
      virtual vector<int> getVelocity() = 0;
   
      virtual void setLocation( vector<int> newValue ) = 0;

      virtual ~IMovingObject(){;}
};

class MovingMock:public IMovingObject
{
    public:
    
    MOCK_METHOD(vector<int>, getVelocity, (), (override));
    MOCK_METHOD(vector<int>, getLocation, (), (override));
    MOCK_METHOD(void, setLocation, (vector<int> newValue) , (override));
};

#endif
