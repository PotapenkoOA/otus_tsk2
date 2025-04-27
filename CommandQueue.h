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
    public:
    CmdQueue()
    {
        list<ICommand*> *pQueue = &m_Queue;
        mutex *pmtx = &mtx;
        //cout<< "CmdQueue(), current scope:"<<IoC::Resolve<map<string, IResolverContainer*>*>( "IoC.Scope.Current" )<<endl; 
               
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
        //cout<< " parent scope:"<<IoC::Resolve<map<string, IResolverContainer*>*>( "IoC.Scope.Parent" )<<endl; 
        /// стратегия положить в очередь
        IoC::Resolve<void, ICommand*>("CommandQueue.Push", cmd);
    }

    ICommand *Pull()
    {
        //cout<< "thread t,parent scope:"<<IoC::Resolve<map<string, IResolverContainer*>*>( "IoC.Scope.Parent" )<<endl; 

        return IoC::Resolve<ICommand*>("CommandQueue.Pull");
    }
};



#endif