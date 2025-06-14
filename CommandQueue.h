#ifndef QUEUE_CMD
#define QUEUE_CMD

#include "command.h"
#include "IoCcontainer.h"

#include <list>
#include <thread>
#include <mutex>
using namespace std;
/// 

class CmdQueue
{
    IObjectPtr m_pScope ;
    shared_ptr<list<ICommandPtr>> m_Queue;
    mutex mtx;

    public:
    CmdQueue()
    {
        m_Queue = make_shared<list<ICommandPtr>>();
        mutex* pmtx = &mtx;   
        
        m_pScope = IoC::Resolve< IObjectPtr,IObjectPtr>( "IoC.Scope.New", nullptr );
        IoC::Resolve<void, IObjectPtr>( "IoC.Scope.Current.Set", m_pScope );

        shared_ptr<list<ICommandPtr>> pQueue = m_Queue;
        IoC::Resolve<ICommandPtr, string,  IResolverContainerPtr>( "IoC.Register", "CommandQueue.Push", 
            make_container (
            function<void(ICommandPtr)>([pQueue,pmtx](ICommandPtr cmd){
                pmtx->lock();
                pQueue->push_back(cmd);
                pmtx->unlock();
            })
        ) )->Execute();
        
        IoC::Resolve<ICommandPtr, string,  IResolverContainerPtr>( "IoC.Register", "CommandQueue.Pull", 
            make_container (
            function<ICommandPtr(void)>([pQueue,pmtx](){
                pmtx->lock();
                //cout<<">>"<<pQueue->size()<<","<<pQueue<<"\n";
                ICommandPtr pCmd = nullptr;
                if(pQueue->size() != 0) {
                    pCmd = pQueue->front();
                    pQueue->pop_front();
                }
                //cout<<">>"<<pQueue->size()<<"\n";
                pmtx->unlock();
                return pCmd;
            })
        ) )->Execute();
        
    }   

    void Push(ICommandPtr cmd)
    {
        IoC::Resolve<void, IObjectPtr>( "IoC.Scope.Current.Set", m_pScope );

        IoC::Resolve<void, ICommandPtr>("CommandQueue.Push", cmd);
    }

    ICommandPtr Pull()
    {
        IoC::Resolve<void, IObjectPtr>( "IoC.Scope.Current.Set", m_pScope );

        return IoC::Resolve<ICommandPtr>("CommandQueue.Pull");
    }

    int GetSize()
    {
        return m_Queue->size();
    }
};

using CmdQueuePtr = std::shared_ptr<CmdQueue>;

#endif