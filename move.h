#ifndef __MOVE
#define __MOVE

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
using namespace std;

class IMove{
    public:
        virtual vector<double> getVelocity() = 0;
        virtual vector<double> getLocation() = 0;
        virtual void setLocation( vector<double> newValue ) = 0;

        virtual void Execute() = 0;
};

class MockMove:public IMove{
    public:
    MOCK_METHOD(vector<double>, getVelocity, (), (override));
    MOCK_METHOD(vector<double>, getLocation, (), (override));
    MOCK_METHOD(void, setLocation, (vector<double> newValue), (override));

    MOCK_METHOD(void,  Execute , (), (override));
};


class Move: public IMove {

    vector<double> m_Location;
    vector<double> m_Velocity;
    
    public: 
        Move();

        vector<double> getLocation() ;
        vector<double> getVelocity() ;
   
        void setLocation( vector<double> newValue ) ;
    
        void Execute();
};

#endif