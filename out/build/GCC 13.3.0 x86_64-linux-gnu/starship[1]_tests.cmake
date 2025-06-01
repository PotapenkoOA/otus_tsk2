add_test([=[JWTVerify.good_jwt_msg]=]  [==[/home/vboxuser/Documents/microservices/otus_3tsk/out/build/GCC 13.3.0 x86_64-linux-gnu/starship]==] [==[--gtest_filter=JWTVerify.good_jwt_msg]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[JWTVerify.good_jwt_msg]=]  PROPERTIES WORKING_DIRECTORY [==[/home/vboxuser/Documents/microservices/otus_3tsk/out/build/GCC 13.3.0 x86_64-linux-gnu]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  starship_TESTS JWTVerify.good_jwt_msg)
