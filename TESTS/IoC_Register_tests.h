#ifndef IOCCONTAINER_TESTS
#define IOCCONTAINER_TESTS

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../IoCcontainer.h"

using ::testing::Return;
using ::testing::Throw;
using ::testing::InSequence;

#include <iostream>
#include <string>
using namespace std;

/// проверить удачный случай регистрации 
TEST(IoCRegisterTest, test0)
{
    IoC::Init();

    IResolverContainer* presolver = new ResolverContainer<function<void(string)>>(
        function<void(string)>( 
            [](string printValue)
            {
                std::cout<< printValue <<std::endl;
            }
        )
    );

    /// проверить регистрацию
    IoC::Resolve< ICommand*, string, IResolverContainer* >(
        "IoC.Register", "aaaaa",  presolver
    )->Execute();

    EXPECT_NO_THROW( (IoC::Resolve<void, string>("aaaaa", "test text")));
}

/// проверить исключения при регистрации не того типа
TEST(IoCRegisterTest, test1)
{
    IoC::Init();

   
    function<void(string)> test_func = function<void(string)>( 
            [](string printValue)
            {
                std::cout<< printValue <<std::endl;
            }
        );
    
    EXPECT_ANY_THROW( 
        (IoC::Resolve< ICommand*, string, function<void(string)> >(
        "IoC.Register", "aaaaa",  test_func
         )->Execute())
    );
}

/// проверить разрешение зависимостей с неправильным запросом
TEST(IoCRegisterTest, test2)
{
    IoC::Init();

    IResolverContainer* presolver = new ResolverContainer<function<void(string)>>(
        function<void(string)>( 
            [](string printValue)
            {
                std::cout<< printValue <<std::endl;
            }
        )
    );

    /// проверить регистрацию
    IoC::Resolve< ICommand*, string, IResolverContainer* >(
        "IoC.Register", "aaaaa",  presolver
    )->Execute();

    EXPECT_ANY_THROW((
        IoC::Resolve<function<void(string)>, string>("aaaaa", "test text")
    ));
}


#endif