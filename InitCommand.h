#include "command.h"
#include "IoC_contaner.h"
#include "ResolverContainer.h"
#include "RegisterCommand.h"

template<typename T,typename ...Args >
class InitCommand: public ICommand
{
    static thread_local map<string, IResolverContainer*> currentScope;

    static map<string, IResolverContainer*> rootScope;

    static bool _alreadyExecutes = false;

    public:

        void Execute()
        {
            if( _alreadyExecutes )
                return;
            
            rootScope["IoC.Register"] = [](Args...){ RegisterCommand(Args...)  } ;  
           
            
            _alreadyExecutes = true;
        }       
};