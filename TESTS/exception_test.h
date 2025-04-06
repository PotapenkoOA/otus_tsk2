#ifndef _EXCEPTIONS_TEST_
#define _EXCEPTIONS_TEST_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "command.h"

using ::testing::Throw;

TEST(ExceptionTests, test1)
{
    GetExceptionCommand *pCmd = new GetExceptionCommand();
   // try{
        

    ASSERT_ANY_THROW(   pCmd->Execute() );
  //  }
  //  catch(IException *ex)
  //  {
    IException *oException = new OrdinaryException("Exception!");

    WriteToLogCommand *pCmd2 = new WriteToLogCommand(pCmd, oException);
    oException->Handle();

    ASSERT_NO_THROW(pCmd2->Execute());
  //  }

}




#endif