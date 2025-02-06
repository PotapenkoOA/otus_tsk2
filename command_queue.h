#ifndef __COMMAND_QUEUE__
#define __COMMAND_QUEUE__ 

#include "command.h"
#include "exception_library.h"
#include <iostream>
#include <list>
using namespace std;

class CommandQueue
{
  list<ICommand*> m_cmd_list;

  bool stop;

  public:
  CommandQueue()
  {
    //m_cmd_list.push_back(new GetExceptionCommand());
  }

  bool AddRuls( ICommand* cmd, IException* exc, Handler f )
  {
    return ExceptionHandler::Register(getType(cmd), getType(exc), f);

  }

  void FirstCommand(ICommand *pCmd)
  {
    m_cmd_list.push_back(pCmd);    
  }

  void MessageLoop()
  {
    stop = m_cmd_list.size() == 0;
      while(!stop)
      {
               
        Tick();

        stop = m_cmd_list.size() == 0 ;
      }
  }

  void Tick()
  {
      ICommand *pCmd = m_cmd_list.front();
        
      try{
        pCmd->Execute() ;
      }
      catch(IException *exc)
      {
        m_cmd_list.push_back(ExceptionHandler::Handle( pCmd, exc ));
      }

      m_cmd_list.pop_front();
  }

  string GetLastCmdType()
  {
    if( m_cmd_list.size() == 0 )
      return "nothing";
    return getType(m_cmd_list.back());
  }

};


#endif