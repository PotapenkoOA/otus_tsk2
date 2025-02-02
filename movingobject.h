#ifndef __MOVINGOBJ
#define __MOVINGOBJ

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
using namespace std;

#include "vector2.h"

class IMovingObject{
    public:
       
      virtual Vector2 getLocation() = 0;
      virtual Vector2 getVelocity() = 0;
   
      virtual void setLocation( Vector2 newValue ) = 0;

      virtual ~IMovingObject(){;}
};

class MovingMock:public IMovingObject
{
    public:
    
    MOCK_METHOD(Vector2, getVelocity, (), (override));
    MOCK_METHOD(Vector2, getLocation, (), (override));
    MOCK_METHOD(void, setLocation, (Vector2 newValue) , (override));
};

#endif
