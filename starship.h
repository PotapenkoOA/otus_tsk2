#ifndef __STARSHIP
#define __STARSHIP

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "move.h"

#include <vector>
using namespace std;

class SpaceShip
{
private:
    /* data */
    vector<double> m_velocity;
    vector<double> m_location;

    IMove *m_pMove;    
public:
    SpaceShip(IMove *pMove, vector<double> vVelocity, vector<double> vLocation);
    ~SpaceShip();

    void move();

    vector<double>  getLocation();
};

#endif
