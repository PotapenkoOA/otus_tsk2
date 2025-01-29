#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <move.h>

#include <vector>
using namespace std;

class MockMove:IMove{
    MOCK_METHOD(vector<double>, getVelocity, (), (override));
    MOCK_METHOD(vector<double>, getLocation, (), (override));
    MOCK_METHOD(void, setLocation, (vector<double> newValue), (override));
};

