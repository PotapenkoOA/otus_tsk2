#ifndef __COMMAND_INTERFACE
#define __COMMAND_INTERFACE

#include "exceptions.h" 
#include <cxxabi.h>

#include <string>
#include <typeinfo>
#include <iostream>

#include "IResolverContainer.h"
using namespace std;

class ICommand{
    public:
    virtual void Execute() = 0;
    virtual ~ICommand() {;}
};

using ICommandPtr = std::shared_ptr<ICommand>;

string getType(ICommand *c)
{
    int status;  
    const type_info& typeInfo = typeid(*c);
    char* demangled = abi::__cxa_demangle(typeInfo.name(), nullptr, nullptr, &status);
    return (status == 0) ? demangled : typeInfo.name();
}

string getType(IException *e)
{
    int status;
    const type_info& typeInfo = typeid(*e);
    char* demangled = abi::__cxa_demangle(typeInfo.name(), nullptr, nullptr, &status);
    return (status == 0) ? demangled : typeInfo.name();
}


string getType(IResolverContainer *c)
{
    int status; 
    const type_info& typeInfo = typeid(*c);
    char* demangled = abi::__cxa_demangle(typeInfo.name(), nullptr, nullptr, &status);
    return (status == 0) ? demangled : typeInfo.name();
}

template<typename T>
string _getType(T *c)
{
    int status;  
   // ResolverContainer<T> *container = dynamic_cast<ResolverContainer<T> *>(c);

    const type_info& typeInfo = typeid(*c);
    char* demangled = abi::__cxa_demangle(typeInfo.name(), nullptr, nullptr, &status);
    return (status == 0) ? demangled : typeInfo.name();
}

class GetExceptionCommand: public ICommand{
    public:
    void Execute() {
        throw new OrdinaryException("Alarm! alarm!!!");
    }
};

class DoNothingCommand: public ICommand{
    public:
    void Execute() {
        ;
    }
};


class WriteToLogCommand: public ICommand {

    string ICommandType;
    string IExceptionType;
    string msg;
    public:

    WriteToLogCommand()
    {

        ICommandType  =  IExceptionType  = msg = "";
    }
    WriteToLogCommand(ICommand *c , IException *e , string msg = "")
    {

        ICommandType  =  getType(c);
        IExceptionType  = getType(e);
        this->msg = msg;
    }
    void Execute()
    {
        if( !IExceptionType.empty() )
        cout<<"Log: Detect an exception ("<<IExceptionType<<") during executing a command("<<ICommandType<<")  "<<msg<<endl;
    }
};

class DoublerCommand: public ICommand {
    ICommand *exceptedCmd;
    IException *lastException;
    public:
    DoublerCommand()
    {
        exceptedCmd = NULL;
    }
    DoublerCommand(ICommand *c,  IException *e)
    {

        exceptedCmd  =  c;
        lastException = e;
        
    }
    void Execute()
    {
        if(exceptedCmd)
            exceptedCmd->Execute();
    }
};

class TriplerCommand: public ICommand {

    ICommand *exceptedCmd;
    IException *lastException;
    public:
    TriplerCommand(){;}
    TriplerCommand(ICommand *c,  IException *e)
    {

        exceptedCmd  =  c;
        lastException = e;
        
    }
    void Execute()
    {
        if(exceptedCmd)
            exceptedCmd->Execute();
    }
};


#endif