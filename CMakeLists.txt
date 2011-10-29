cmake_minimum_required (VERSION 2.8)

ENABLE_TESTING()

project (EduGame)
set (EduGame_VERSION_MAJOR 0)
set (EduGame_VERSION_MINOR 1)

SET (SDKROOT "/Developer/SDKs/MacOSX10.6.sdk")
SET (CMAKE_OSX_SYSROOT "${SDKROOT}")
SET (CMAKE_OSX_ARCHITECTURES "i386")
SET (CMAKE_CXX_COMPILER /usr/bin/g++)
SET (CMAKE_EXE_LINKER_FLAGS -rpath boost/lib)
ADD_DEFINITIONS(-g)


##############################
## Adding Third Party Files ##
##############################

add_subdirectory(third_party)

FILE(GLOB INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/*/include")
FOREACH(s ${INCLUDE_DIRS})
include_directories(${s})
ENDFOREACH()

FILE(GLOB STATIC_LIBS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*/lib/*.a")
FOREACH(s ${STATIC_LIBS_FILES} )
  STRING(REGEX REPLACE ".*/lib(.*)\\.a" "\\1" name "${s}")
  add_library(${name} STATIC IMPORTED)
   set_property(TARGET ${name} PROPERTY
                IMPORTED_LOCATION ${s})
  MESSAGE("Adding library \"${name}\" from location \"${s}\"")
ENDFOREACH()

SET(STATIC_LIBS Irrlicht boost_python )
SET(DYNAMIC_LIBS python dl)

include_directories(src)

FILE(GLOB_RECURSE SRCS "src/**.cpp")
FILE(GLOB_RECURSE TEST_SRCS "src/test/**.cpp")

# Remove test files from $SRC
FOREACH(t ${TEST_SRCS})
  LIST(REMOVE_ITEM SRCS ${t})
ENDFOREACH()

if(APPLE)
  FILE(GLOB MAC_RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/OSXResources/*")
  set_source_files_properties( ${MAC_RESOURCES} PROPERTIES MAC_OSX_PACKAGE_LOCATION Resources)
  LIST(APPEND SRCS ${MAC_RESOURCES})
ENDIF()

add_executable(edugame WIN32 MACOSX_BUNDLE ${SRCS})
target_link_libraries(edugame Irrlicht boost_python ${EXTRA_LIBS} python dl)
set (LIBS ${LIBS} boost_python)

IF(APPLE)
  set_target_properties(edugame PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/OSXResources/Info.plist")
ENDIF()

install(TARGETS edugame RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR} BUNDLE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})

LIST(APPEND TEST_ALL_SRCS ${SRCS})
FILE(GLOB main "src/main.cpp")
LIST(REMOVE_ITEM TEST_ALL_SRCS ${main})
FOREACH(t ${TEST_SRCS})
  STRING(REGEX REPLACE ".*/(.*)\\.cpp" "\\1" name "${t}")
  add_executable(${name} ${t} ${TEST_ALL_SRCS})
  target_link_libraries(${name} ${STATIC_LIBS} ${EXTRA_LIBS} ${DYNAMIC_LIBS})
  add_test(${name} ${name})
ENDFOREACH()
