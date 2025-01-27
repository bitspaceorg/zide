if (BUILD_TESTING)
  add_executable(zide_tests math_tests.cpp ../src/utils/zmath.cpp)
  target_link_libraries(zide_tests PRIVATE GTest::gtest_main)

  include(GoogleTest)
  gtest_discover_tests(zide_tests)
endif()
