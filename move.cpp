#include <move.h>

void Move::Execute()
{
   setLocation( Plus(getLocation(), getVelocitty())) ;
}
