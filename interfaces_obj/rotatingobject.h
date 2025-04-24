#ifndef __ROTATINGOBJ
#define __ROTATINGOBJ

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;

#include "../older_task/angle.h"

class IRotatingObject{
public:
virtual Angle getAngle() = 0;
virtual Angle getAngularVelocity() = 0;
virtual void setAngle(Angle a) = 0;
};

class RotatingMock : public IRotatingObject {
  public:
    MOCK_METHOD(Angle, getAngularVelocity, (), (override));
    MOCK_METHOD(Angle, getAngle, (), (override));
    MOCK_METHOD(void, setAngle, (Angle a) , (override));
};

#endif
