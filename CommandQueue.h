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
    list<ICommandPtr> m_Queue;
    mutex mtx;

    public:
    CmdQueue()
    {
        list<ICommandPtr> *pQueue = &m_Queue;
        mutex *pmtx = &mtx;
        
        IoC::Resolve<ICommandPtr, string,  IResolverContainer*>( "IoC.Register", "CommandQueue.Push", new ResolverContainer< function<void(ICommandPtr)>> (
            function<void(ICommandPtr)>([pQueue,pmtx](ICommandPtr cmd){
                pmtx->lock();
                pQueue->push_back(cmd);
                pmtx->unlock();
            })
        ) )->Execute();
        
        IoC::Resolve<ICommandPtr, string,  IResolverContainer*>( "IoC.Register", "CommandQueue.Pull", new ResolverContainer< function<ICommandPtr(void)>> (
            function<ICommandPtr(void)>([pQueue,pmtx](){
                pmtx->lock();
                ICommandPtr pCmd = nullptr;
                if(pQueue->size() != 0) {
                    pCmd = pQueue->front();
                    pQueue->pop_front();
                }
                pmtx->unlock();
                return pCmd;
            })
        ) )->Execute();
        
    }   

    void Push(ICommandPtr cmd)
    {
        IoC::Resolve<void, ICommandPtr>("CommandQueue.Push", cmd);
    }

    ICommandPtr Pull()
    {
        return IoC::Resolve<ICommandPtr>("CommandQueue.Pull");
    }
};

using CmdQueuePtr = std::shared_ptr<CmdQueue>;

#endif