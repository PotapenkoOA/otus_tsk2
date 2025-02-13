#ifndef _EXCEPTIONS_
#define _EXCEPTIONS_

#include <iostream>
using namespace std;

class IException: public exception {

    public:

    virtual void Handle() = 0;

    virtual ~IException() {;}
    
};

class OrdinaryException: public IException{

string m_description;
    public:
    OrdinaryException()
    {
        m_description = "no exception";

    }

    OrdinaryException(string description)
    {
        m_description = description;

    }
    void Handle(){

        //TODO: do something
        cout<<m_description;        
    }
    
};

class CommandException: public OrdinaryException{

};



#endif