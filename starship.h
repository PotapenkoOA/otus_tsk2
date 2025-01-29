#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <move.h>

#include <vector>
using namespace std;

class cstarship
{
private:
    /* data */
    vector<double> m_velocity;
    vector<double> m_location;

    IMove *pMove;
    
public:
    cstarship(/* args */);
    ~cstarship();

    void move();
};

