#ifndef THREAD_CMD
#define THREAD_CMD

#include "command.h"
#include "CommandQueue.h"
#include "exception_library.h"
#include "states.h"

#include <iostream>
using namespace std;
/// 

class StartCmd: public ICommand
{
    IStatePtr m_pState;
    
    public:
    StartCmd(IStatePtr pStartState)
    {
        m_pState =  pStartState;
      
    }
    void Execute()
    {        
        thread t(
            [&](IStatePtr pState)
            {
                while( pState =  pState->Handle() )
                { 
                }
                
            }, ref(m_pState)
        );
        t.join();
    }
};

class HardStopCmd: public ICommand
{    
    public:
    HardStopCmd()
    {;}
    void Execute()
    {
        IoC::Resolve<ICommand*, string,  IResolverContainer*>( "IoC.Register", "CommandQueue.Pull", 
            new ResolverContainer< function<ICommand*(void)>> (
            function<ICommand*(void)>([](){
                return nullptr;
            })
        ) )->Execute();    
    }
};

class SoftStopCmd: public ICommand
{
    public:
    SoftStopCmd()
    {;}
    void Execute()
    {
        IoC::Resolve<ICommand*, string,  IResolverContainer*>( "IoC.Register", "CommandQueue.Push", 
            new ResolverContainer< function<void(ICommand*)>> ( 
                function<void(ICommand*)>([](ICommand* cmd){}) 
            ) )->Execute();
    }
};



#endif