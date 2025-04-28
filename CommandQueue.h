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
    list<ICommand*> m_Queue;
    mutex mtx;
    condition_variable conditional_var;
    bool conditional = false;

    public:
    CmdQueue()
    {
        list<ICommand*> *pQueue = &m_Queue;
        mutex *pmtx = &mtx;
               
        IoC::Resolve<ICommand*, string,  IResolverContainer*>( "IoC.Register", "CommandQueue.Push", new ResolverContainer< function<void(ICommand*)>> (
            function<void(ICommand*)>([pQueue,pmtx](ICommand* cmd){
                pmtx->lock();
                pQueue->push_back(cmd);
                pmtx->unlock();
            })
        ) )->Execute();

        IoC::Resolve<ICommand*, string,  IResolverContainer*>( "IoC.Register", "CommandQueue.Pull", new ResolverContainer< function<ICommand*(void)>> (
            function<ICommand*(void)>([pQueue,pmtx](){
                pmtx->lock();
                ICommand* pCmd = nullptr;
                if(pQueue->size() != 0) {
                    pCmd = pQueue->front();
                    pQueue->pop_front();
                }
                pmtx->unlock();
                return pCmd;
            })
        ) )->Execute();
    }   

    void Push(ICommand* cmd)
    {
        IoC::Resolve<void, ICommand*>("CommandQueue.Push", cmd);
    }

    ICommand *Pull()
    {
        return IoC::Resolve<ICommand*>("CommandQueue.Pull");
    }
};



#endif