#ifndef __STATE_CHANGE_CMD__
#define __STATE_CHANGE_CMD__

#include "command.h"
#include "IoCcontainer.h"
#include "states.h"
#include "CommandQueue.h"

#include <list>

using namespace std;

class IState;

class _HardStopCmd: public ICommand
{
    ICommandPtr m_cmd;
    public:
    _HardStopCmd()
    {}

    void Execute()
    {
        // устанавливаем нулевое состояние
        IoC::Resolve<  ICommandPtr, string, IResolverContainerPtr >("IoC.Register", "State", 
        make_container (
            function<IStatePtr()>([](){
            return nullptr;
            })
        ))->Execute();
    }
};

class RunCmd: public ICommand
{
    CmdQueuePtr m_cmdqueue;
    public:
    RunCmd( CmdQueuePtr cmdqueue ):
    m_cmdqueue( cmdqueue )
    {}

    void Execute()
    {
        // устанавливаем обычное состояние
        IoC::Resolve<  ICommandPtr, string, IResolverContainerPtr >("IoC.Register", "State", 
        make_container (
        function<IStatePtr()>([&](){
           return make_shared<OrdinaryState>(m_cmdqueue);
        })
        ))->Execute();
    }
};

class MoveToCmd: public ICommand
{
    CmdQueuePtr m_cmd_from;
    CmdQueuePtr m_cmd_to;
    public:
    MoveToCmd(CmdQueuePtr cq_from, CmdQueuePtr cq_to)
    :m_cmd_from(cq_from), m_cmd_to(cq_to)
    {}

    void Execute()
    {
        // устанавливаем moving to состояние
        IoC::Resolve<  ICommandPtr, string, IResolverContainerPtr >("IoC.Register", "State", 
        make_container (
            function<IStatePtr()>([&](){
                //cout<<"MoveToCmd\n";
                return make_shared<MovingToState>(m_cmd_from, m_cmd_to);
            })
        ))->Execute();
    }
};
#endif