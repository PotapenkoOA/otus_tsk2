
#include <vector>
using namespace std;

class IMove{
    virtual vector<double> getVelocity() = 0;
    virtual vector<double> getLocation() = 0;
    virtual void setLocation( vector<double> newValue ) = 0;
};

class Move: public IMove{

    public: 
    Move(IMove *obj);

    void Execute();
};