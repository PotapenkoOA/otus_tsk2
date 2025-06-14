#ifndef __STATES__
#define __STATES__

#include "command.h"
#include "CommandQueue.h"
#include "IoCcontainer.h"

using namespace std;

/// 
class IState{
    public:
    
    virtual shared_ptr<IState> Handle() = 0;
};

using IStatePtr = shared_ptr<IState>;

class OrdinaryState : public IState
{
    mutex m_mtx;
    CmdQueuePtr m_pQueue;
    public: 
    OrdinaryState( CmdQueuePtr pQueue )
    {
        m_pQueue = pQueue;
    }

    IStatePtr Handle()
    {
        ICommandPtr pCmd = m_pQueue->Pull();
        if( !pCmd )
            return nullptr;

        try{
            pCmd->Execute() ;
        }
        catch(IException *exc)
        {
            m_pQueue->Push(ExceptionHandler::Handle( pCmd, exc ));
        }

        return IoC::Resolve<IStatePtr>("State");
    }
};

class _HardStopCmd;

class MovingToState : public IState
{
    CmdQueuePtr m_pOldQueue;
    CmdQueuePtr m_pNewQueue;
    public: 
    MovingToState( CmdQueuePtr pOldQueue , CmdQueuePtr pNewQueue )
    {
        m_pOldQueue = pOldQueue;
        m_pNewQueue = pNewQueue;
    }

    IStatePtr Handle()
    {
        //cout<<"Pull\n";
        
        ICommandPtr pCmd = m_pOldQueue->Pull();
        {
            if( !pCmd )
                return nullptr;            
            
            try{
                m_pNewQueue->Push(pCmd);
            }
            catch(IException *exc)
            {
                m_pNewQueue->Push(ExceptionHandler::Handle( pCmd, exc ));
            }
        }

        return IoC::Resolve<IStatePtr>("State");
    }
};

#endif