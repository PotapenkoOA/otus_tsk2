#include <starship.h>

SpaceShip::SpaceShip(IMove *pMove,vector<double> vVelocity, vector<double> vLocation)
{
    m_pMove = pMove;

    m_location = vLocation;

    m_velocity = vVelocity;
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::move()
{
    //m_pMove->getLocation();
}

vector<double> SpaceShip::getLocation()
{
    return m_location;
}
