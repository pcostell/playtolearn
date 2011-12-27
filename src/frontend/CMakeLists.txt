
FILE(GLOB_RECURSE SRCS "**.cpp")

# Remove main from ALL_NONMAIN_SRCS
LIST(APPEND ALL_NONMAIN_SRCS ${SRCS})
FILE(GLOB main "FEEngine.cpp")
LIST(REMOVE_ITEM ALL_NONMAIN_SRCS ${main})

add_library(playtolearnlibrary_frontend ${ALL_NONMAIN_SRCS})
target_link_libraries(playtolearnlibrary_frontend
                      Irrlicht)
add_dependencies(playtolearnlibrary_frontend Irrlicht)