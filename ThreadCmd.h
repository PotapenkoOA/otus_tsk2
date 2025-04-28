#ifndef THREAD_CMD
#define THREAD_CMD

#include "command.h"
#include "CommandQueue.h"
#include "exception_library.h"

#include <iostream>
using namespace std;
/// 

class StartCmd: public ICommand
{
    CmdQueue *m_pQueue;
    
    public:
    StartCmd(CmdQueue *pQueue)
    {
        m_pQueue =  pQueue;
      
    }
    void Execute()
    {        
        thread t(
            [&](CmdQueue *pQueue)
            {
                ICommand *pCmd = pQueue->Pull();
                while( pCmd != nullptr )
                {
                    
                    try{
                        pCmd->Execute() ;
                    }
                    catch(IException *exc)
                    {
                        pQueue->Push(ExceptionHandler::Handle( pCmd, exc ));
                    }
                    pCmd = pQueue->Pull();
                }
                
            }, ref(m_pQueue)
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
        IoC::Resolve<ICommand*, string,  IResolverContainer*>( "IoC.Register", "CommandQueue.Pull", new ResolverContainer< function<ICommand*(void)>> (
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
            new ResolverContainer< function<void(ICommand*)>> ( function<void(ICommand*)>([](ICommand* cmd){}) ) )->Execute();
    }
};



#endif