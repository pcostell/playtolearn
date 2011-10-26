include(ExternalProject)
include(FindPythonLibs)

######################
## GENERIC PACKAGES ##
######################

find_package(GLUT)
find_package(OpenGL)

IF(NOT PYTHONLIBS_FOUND)
  MESSAGE(FATAL_ERROR "Could not find python libraries.")
ENDIF()


#include_directories(/usr/include/python2.7)
#link_directories(/usr/lib)

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

IF(APPLE)
  set(BOOST_ARGS ${BOOST_ARGS} toolset=darwin architecture=x86 address-model=32 threading=single)
ENDIF()


ExternalProject_Add(boost
  PREFIX boost/
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
  set(IRRLICHT_BUILD_COMMAND cd source/Irrlicht/MacOSX && xcodebuild -project MacOSX.xcodeproj -sdk ${SDKROOT} -arch i386)
  set(IRRLICHT_INSTALL_COMMAND mkdir -p ../../lib && cp <SOURCE_DIR>/source/Irrlicht/MacOSX/build/Release/libIrrlicht.a ../../lib/ && cp -r <SOURCE_DIR>/include ../../)
ELSE()
  set(IRRLICHT_BUILD_COMMAND "")
  set(IRRLICHT_INSTALL_COMMAND "")
ENDIF()

ExternalProject_Add(irrlicht
  PREFIX irrlicht/
  URL http://downloads.sourceforge.net/irrlicht/irrlicht-1.7.2.zip
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND ""
  BUILD_COMMAND  ${IRRLICHT_BUILD_COMMAND}
  INSTALL_COMMAND ${IRRLICHT_INSTALL_COMMAND}
)

##################
## Adding Files ##
##################

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