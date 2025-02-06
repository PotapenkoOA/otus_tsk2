#ifndef _EXPECTATION_LIBRARY_
#define _EXPECTATION_LIBRARY_

#include "command.h"
#include "exceptions.h"


#include <map>
#include <string>
#include <iostream>
using namespace std;

typedef ICommand* (*Handler)(ICommand* c, IException* e);

class ExceptionHandler
{
    static map<string, map< string , Handler>> m_ExceptionLibrary;
public:
   
    static ICommand *Handle( ICommand *c, IException *e)
    {
        string CommandType =  getType(c);
        string ExceptionType =  getType(e);

        if( m_ExceptionLibrary.count(CommandType) > 0  )
        {
            if( m_ExceptionLibrary[CommandType].count(ExceptionType) > 0 )
            {
                if( m_ExceptionLibrary[CommandType][ExceptionType] != NULL )
                {
                    return m_ExceptionLibrary[CommandType][ExceptionType](c,e);
                }else cout << "m_ExceptionLibrary[CommandType][ExceptionType] == NULL" <<endl;
            }else cout << "m_ExceptionLibrary[CommandType].count(ExceptionType) > 0 " << m_ExceptionLibrary[CommandType].count(ExceptionType)  <<endl; 
        }else cout<< "m_ExceptionLibrary.count(CommandType)" << m_ExceptionLibrary.count(CommandType)<<endl;
        return new DoNothingCommand();
    }
    static bool Register(string CommandType , string ExceptionType , Handler h )
    {
       m_ExceptionLibrary[CommandType][ExceptionType] = h;

       return false;
    }

};

map<string, map< string , Handler>> ExceptionHandler::m_ExceptionLibrary ;

#endif