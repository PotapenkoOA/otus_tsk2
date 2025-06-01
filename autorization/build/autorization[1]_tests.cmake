add_test([=[AUTO_SRVR.good_jwt_msg]=]  /home/vboxuser/Documents/microservices/autorization/build/autorization [==[--gtest_filter=AUTO_SRVR.good_jwt_msg]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AUTO_SRVR.good_jwt_msg]=]  PROPERTIES WORKING_DIRECTORY /home/vboxuser/Documents/microservices/autorization/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  autorization_TESTS AUTO_SRVR.good_jwt_msg)
