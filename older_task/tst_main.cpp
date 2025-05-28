#include "command_queue.h"

int main(int argc, char* argv[])
{
  CommandQueue co;

  co.AddRuls( new GetExceptionCommand(), new OrdinaryException(), &func2 );
  co.AddRuls( new DoublerCommand(),      new OrdinaryException(), &func3 );
  co.AddRuls( new TriplerCommand(),      new OrdinaryException(), &func );

  cout<<"GetLastCmdType "<< co.GetLastCmdType()<<endl;
  co.MessageLoop();
  cout<<"GetLastCmdType "<< co.GetLastCmdType()<<endl;
       
  return 0;
}