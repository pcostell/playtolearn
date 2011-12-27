FILE(GLOB_RECURSE TEST_SRCS "**.cpp")
SET(test_names "")
FOREACH(t ${TEST_SRCS})
  STRING(REGEX REPLACE ".*/(.*)\\.cpp" "\\1" name "${t}")
  LIST(APPEND test_names ${name})
  add_executable(${name} EXCLUDE_FROM_ALL ${t})
  target_link_libraries(${name} playtolearnlibrary ${DYNAMIC_LIBS} boost_unit_test_framework)
  add_test(${name} ${name})
  add_dependencies(${name} playtolearnlibrary)
ENDFOREACH()

# This will explicitly build all the tests. We need this
# because we added EXCLUDE_FROM_ALL to the test exes. This
# greatly speeds up compilation because when we change code
# in our main library, we don't need to build our tests.
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
                  DEPENDS ${test_names})