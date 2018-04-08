
 INCLUDE_DIRECTORIES(include)

 set(Tests
     test/MissionTumblerTests.cpp
     src/MissionTumbler.cpp ../MissionSystem/BasicGoal.cpp ../MissionSystem/Reward.cpp ../MissionSystem/Mission.cpp)
 add_executable(MissionTumblerTests ${Tests})

 add_definitions (-DBOOST_TEST_DYN_LINK)

 target_link_libraries(MissionTumblerTests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
 
 add_test (NAME MissionTumblerTests COMMAND MissionTumblerTests)
