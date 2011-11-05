cmake_minimum_required (VERSION 2.8)

ENABLE_TESTING()

project (EduGame)
set (EduGame_VERSION_MAJOR 0)
set (EduGame_VERSION_MINOR 1)

SET (SDKROOT "/Developer/SDKs/MacOSX10.6.sdk")
SET (CMAKE_OSX_SYSROOT "${SDKROOT}")
SET (CMAKE_OSX_ARCHITECTURES "i386")
#SET (CMAKE_CXX_COMPILER /usr/bin/g++)
ADD_DEFINITIONS(-g)

###############################################
#           THIRD PARTY LIBRARIES             #
###############################################

include(ExternalProject)

set (Python_ADDITIONAL_VERSIONS 3.1)
set (FIND_LIBRARY_USE_LIB64_PATHS true)
include(FindPythonLibs)

if(UNIX)
	FIND_LIBRARY(X11_LIBRARY X11)
endif()

MESSAGE("X11: ${X11_FOUND}")

######################
## GENERIC PACKAGES ##
######################

find_package(GLUT)
find_package(OpenGL)

IF(NOT PYTHONLIBS_FOUND)
  MESSAGE(FATAL_ERROR "Could not find python libraries.")
ENDIF()

STRING(REGEX REPLACE ".*/libpython3(.*)\\.so" "\\1" PYTHON_VERSION_3 "${PYTHON_LIBRARIES}")
STRING(REGEX REPLACE ".*/libpython2(.*)\\.so" "\\1" PYTHON_VERSION_2 "${PYTHON_LIBRARIES}")

MESSAGE("${PYTHON_VERSION_3}")
IF (${PYTHON_VERSION_3})
ADD_DEFINITIONS(-DPYTHON_VERSION_3)
ENDIF()

MESSAGE("Python include directory: ${PYTHON_INCLUDE_DIRS}")
MESSAGE("Python library: ${PYTHON_LIBRARIES}")

include_directories(${PYTHON_INCLUDE_DIRS})
# Don't need to link since PYTHON_LIBRARIES IS THE LIBRARY
#link_directories(${PYTHON_LIBRARIES})

  #add_library(python SHARED IMPORTED)
  #set_property(TARGET python PROPERTY
  #              IMPORTED_LOCATION ${PYTHON_LIBRARIES})


######################
## APPLE FRAMEWORKS ##
######################

IF(APPLE)
   INCLUDE_DIRECTORIES ( /Developer/Headers/FlatCarbon )
   FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
   FIND_LIBRARY(CARBON_LIBRARY Carbon)
   FIND_LIBRARY(COCOA_LIBRARY Cocoa )
   FIND_LIBRARY(IOKIT_LIBRARY IOKit )
   FIND_LIBRARY(CORE_FOUNDATION_LIBRARY CoreFoundation )
   MARK_AS_ADVANCED (CARBON_LIBRARY
                     COCOA_LIBRARY
                     IOKIT_LIBRARY
                     CORE_FOUNDATION_LIBRARY
                     OPENGL_LIBRARY)
   SET(EXTRA_LIBS ${CARBON_LIBRARY} ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${CORE_FOUNDATION_LIBRARY} ${OPENGL_LIBRARY})
ENDIF()


#######################
## BOOOST LIBRARIES ##
#######################

set(BOOST_LIBS thread,python,test)
set(BOOST_ARGS include=${PYTHON_INCLUDE_DIRS})

IF(APPLE)
  set(BOOST_ARGS ${BOOST_ARGS} toolset=darwin architecture=x86 address-model=32 threading=single)
ENDIF()


ExternalProject_Add(boost
  PREFIX third_party/boost/
  BUILD_IN_SOURCE 1
  SVN_REPOSITORY http://svn.boost.org/svn/boost/tags/release/Boost_1_47_0/
  #GIT_REPOSITORY git://gitorious.org/boost/cmake.git
  #GIT_TAG cmake-1.47.0
  CONFIGURE_COMMAND <SOURCE_DIR>/bootstrap.sh --with-python-version=2.7 --prefix="<INSTALL_DIR>" --libdir="<INSTALL_DIR>/lib" --with-libraries=${BOOST_LIBS}
  BUILD_COMMAND <SOURCE_DIR>/bjam ${BOOST_ARGS} install
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
)

########################
## IRRLICHT LIBRARIES ##
########################

IF(APPLE)
  set(IRRLICHT_BUILD_COMMAND cd <SOURCE_DIR>/source/Irrlicht/MacOSX && xcodebuild -project MacOSX.xcodeproj -sdk ${SDKROOT} -arch i386)
  set(IRRLICHT_INSTALL_COMMAND mkdir -p ../../lib && cp <SOURCE_DIR>/source/Irrlicht/MacOSX/build/Release/libIrrlicht.a ../../lib/ && cp -r <SOURCE_DIR>/include ../../)
ELSE()
  set(IRRLICHT_BUILD_COMMAND cd source/Irrlicht && make)
  set(IRRLICHT_INSTALL_COMMAND mkdir -p ../lib && cp <SOURCE_DIR>/lib/Linux/libIrrlicht.a  ../lib/ && cp -r <SOURCE_DIR>/include ../)
ENDIF()

ExternalProject_Add(irrlicht
  PREFIX irrlicht/
  URL http://www.stanford.edu/~pcostell/irrlicht-1.7.2.tar.gz
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND ""
  BUILD_COMMAND  ${IRRLICHT_BUILD_COMMAND}
  INSTALL_COMMAND ${IRRLICHT_INSTALL_COMMAND}
)

##################
## Adding Files ##
##################

FILE(GLOB _INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/*/include")
MESSAGE("DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
FOREACH(s ${_INCLUDE_DIRS})
MESSAGE("Including: ${s}")
include_directories(${s})
ENDFOREACH()

FILE(GLOB STATIC_LIBS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/third_party/*/lib/*.a")
FOREACH(s ${STATIC_LIBS_FILES} )
  STRING(REGEX REPLACE ".*/lib(.*)\\.a" "\\1" name "${s}")
  add_library(${name} STATIC IMPORTED)
   set_property(TARGET ${name} PROPERTY
                IMPORTED_LOCATION ${s})
  MESSAGE("Adding library \"${name}\" from location \"${s}\"")
ENDFOREACH()

SET(STATIC_LIBS Irrlicht boost_python )
SET(DYNAMIC_LIBS python2.6 dl)

if(UNIX AND NOT APPLE)
	SET(DYNAMIC_LIBS ${DYNAMIC_LIBS} GL GLU Xxf86vm Xext X11)
endif()

#############
## SOURCES ##
#############

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

add_executable(playtolearn WIN32 MACOSX_BUNDLE ${SRCS})
target_link_libraries(playtolearn Irrlicht boost_python ${EXTRA_LIBS} ${DYNAMIC_LIBS})
set (LIBS ${LIBS} boost_python)

IF(APPLE)
  set_target_properties(playtolearn PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/OSXResources/Info.plist")
ENDIF()

install(TARGETS playtolearn RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR} BUNDLE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})

LIST(APPEND TEST_ALL_SRCS ${SRCS})
FILE(GLOB main "src/frontend/FEEngine.cpp")
LIST(REMOVE_ITEM TEST_ALL_SRCS ${main})
FOREACH(t ${TEST_SRCS})
  STRING(REGEX REPLACE ".*/(.*)\\.cpp" "\\1" name "${t}")
  add_executable(${name} ${t} ${TEST_ALL_SRCS})
  target_link_libraries(${name} ${STATIC_LIBS} ${EXTRA_LIBS} ${DYNAMIC_LIBS} boost_unit_test_framework)
  add_test(${name} ${name})
ENDFOREACH()
