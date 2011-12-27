
FILE(GLOB_RECURSE SRCS "**.cpp")

FILE(GLOB_RECURSE PRE_MOC_FILES "**.hpp")
QT4_WRAP_CPP(HEADERS_MOC ${PRE_MOC_FILES})
LIST(APPEND SRCS ${HEADERS_MOC})

# Remove main from ALL_NONMAIN_SRCS
LIST(APPEND ALL_NONMAIN_SRCS ${SRCS})
FILE(GLOB main "main.cpp")
LIST(REMOVE_ITEM ALL_NONMAIN_SRCS ${main})

add_library(playtolearnlibrary_ui ${ALL_NONMAIN_SRCS})
target_link_libraries(playtolearnlibrary_ui
                      playtolearnlibrary_backend
                      ${QT_LIBRARIES})
add_dependencies(playtolearnlibrary_ui
                 playtolearnlibrary_backend)