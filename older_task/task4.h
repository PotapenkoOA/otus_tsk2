#pragma once

#include "command.h"
#include "math.h"
#include <iostream>
using namespace std;

class CheckFuelComamnd : public ICommand
{
    int *m_fuelLevel;
    int m_minValue;
    public:
    CheckFuelComamnd(int *fuelLevel, int minValue = 0)
    {
        m_fuelLevel = fuelLevel;
        m_minValue = minValue;
    }
    void Execute()
    {
        //cout<<"level:"<< *m_fuelLevel<< " minValue: "<<m_minValue<<endl;
        if( *m_fuelLevel < m_minValue )
            throw CommandException();
    }
};

class BurnFuelCommand  : public ICommand
{
    int *m_fuelLevel;
    int m_BurnFuelVelocity;
    public:
    BurnFuelCommand(int *fuelLevel, int BurnFuelVelocity)
    {
        m_fuelLevel = fuelLevel;
        m_BurnFuelVelocity = BurnFuelVelocity;
    }
    void Execute()
    {
        if(  *m_fuelLevel - m_BurnFuelVelocity  > 0)
            *m_fuelLevel -= m_BurnFuelVelocity;
        else *m_fuelLevel = 0;
    }
};

class MacroCommand  : public ICommand
{
    ICommand* *m_pCommands;
    int m_commandCount;
    public:
    MacroCommand(ICommand **pCommandArray, int commandCount)
    {
        m_commandCount = commandCount;
        m_pCommands = pCommandArray;
    }
    void Execute()
    {
        for( int i = 0; i < m_commandCount; i++ )
        {
            m_pCommands[i]->Execute();
        }
    }
};

class IVelocity
{
    public:
    virtual Vector2 get() = 0;
    virtual void set( Vector2 newVelocity ) = 0;   
};

class VelocityMock: public IVelocity
{
    public:
    MOCK_METHOD(Vector2, get, (), (override)); 
    MOCK_METHOD(void, set, (Vector2 newVelocity), (override));  
};


// изменение скорости при повороте
// макро команда изменение и 
class ChangeVelocityCommand   : public ICommand
{
    IVelocity *pObject;
    Angle m_a;
    public:
    ChangeVelocityCommand ( IVelocity *obj, Angle a )
    {
        pObject = obj;
        m_a = a;
    }
    void Execute()
    {
        Vector2 b = pObject->get();
        Vector2 c = b.rotate(m_a);
        pObject->set(c);
        return;
    }
};

